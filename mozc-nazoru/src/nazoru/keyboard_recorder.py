# -*- coding: utf-8 -*-
#
# Copyright 2018 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

from __future__ import print_function

from enum import Enum
import datetime
import fcntl
import os
import struct
import sys
import termios

try:
  import evdev
except ImportError:
  evdev = None

def _set_raw_mode_stdin():
  fno = sys.stdin.fileno()
  attr_old = termios.tcgetattr(fno)
  fcntl_old = fcntl.fcntl(fno, fcntl.F_GETFL)

  attr_new = termios.tcgetattr(fno)
  attr_new[3] = attr_new[3] & ~termios.ECHO & ~termios.ICANON
  termios.tcsetattr(fno, termios.TCSADRAIN, attr_new)

  fcntl.fcntl(fno, fcntl.F_SETFL, fcntl_old | os.O_NONBLOCK)

  def reset_raw_mode():
    termios.tcsetattr(fno, termios.TCSANOW, attr_old)
    fcntl.fcntl(fno, fcntl.F_SETFL, fcntl_old)

  return reset_raw_mode

def _set_raw_mode_general(f):
  fno = f.fileno()
  fcntl_old = fcntl.fcntl(fno, fcntl.F_GETFL)
  fcntl.fcntl(fno, fcntl.F_SETFL, fcntl_old | os.O_NONBLOCK)

  def reset_raw_mode():
    fcntl.fcntl(fno, fcntl.F_SETFL, fcntl_old)

  return reset_raw_mode

class KeyboardRecorder():
  def __init__(self, verbose=False):
    self._verbose = verbose

  def record(self):
    return (None, None)

  def log(self, *args, **kwargs):
    # TODO(shimazu): Use logger.
    if self._verbose:
      print(*args, file=sys.stderr, **kwargs)

class KeyboardRecorderFromConsole(KeyboardRecorder):
  def __init__(self, verbose=False):
    KeyboardRecorder.__init__(self, verbose)
    self.log('Input from console')

  def _read_ansi_escape(self):
    seq = sys.stdin.read(1)
    if seq == '[':
      # CSI code
      # ['\e', '[', Rep (optional), Code]
      code = sys.stdin.read(1)
      rep = 1
      if code.isdigit():
        rep = int(code)
        code = sys.stdin.read(1)
      if code == 'A':
        return (None, 'KEY_UP')
      if code == 'B':
        return (None, 'KEY_DOWN')
      if code == 'C':
        return (None, 'KEY_RIGHT')
      if code == 'D':
        return (None, 'KEY_LEFT')
      if code == '~':
        if rep == 3:
          return (None, 'KEY_DELETE')
      self.log('it was unknown code: ' +
               'rep={}, code={}'.format(rep, code))
    else:
      self.log('unknown seq: {}'.format(seq))
    return (None, None)

  def record(self):
    """
    Returns a tuple of |data| and |command|.
    |data|: an array of tuples of keys and time from the first character.
    |command|: None
    """
    recording = False
    start_time = None
    last_time = None
    wait_seconds = 0.5
    data = []
    reset_raw_mode = _set_raw_mode_stdin()
    try:
      while 1:
        try:
          key = sys.stdin.read(1)
        except IOError:
          key = None
        finally:
          now = datetime.datetime.now()
        if key == '\x1b':
          return self._read_ansi_escape();
        elif key == '\n':
          return (None, 'KEY_ENTER')
        elif key == '\b' or key == '\x7f':
          return (None, 'KEY_BACKSPACE')
        elif key:
          if not recording:
            recording = True
            start_time = datetime.datetime.now()
          elapsed_time = now - start_time
          elapsed_ms = int(elapsed_time.total_seconds() * 1000)
          last_time = now
          data.append((key, elapsed_ms))
          self.log(key, elapsed_ms)
        if last_time and (now - last_time).total_seconds() > wait_seconds:
          break
    finally:
      reset_raw_mode()
    return (data, None)

class KeyboardRecorderFromEvdev(KeyboardRecorder):
  KEYS = {
      2: '1',
      3: '2',
      4: '3',
      5: '4',
      6: '5',
      7: '6',
      8: '7',
      9: '8',
      10: '9',
      11: '0',
      12: '-',
      13: '=',
      16: 'q',
      17: 'w',
      18: 'e',
      19: 'r',
      20: 't',
      21: 'y',
      22: 'u',
      23: 'i',
      24: 'o',
      25: 'p',
      26: '[',
      27: ']',
      30: 'a',
      31: 's',
      32: 'd',
      33: 'f',
      34: 'g',
      35: 'h',
      36: 'j',
      37: 'k',
      38: 'l',
      39: ';',
      40: '\'',
      43: '\\',
      44: 'z',
      45: 'x',
      46: 'c',
      47: 'v',
      48: 'b',
      49: 'n',
      50: 'm',
      51: ',',
      52: '.',
      53: '/'
  }
  WAIT_SECONDS = 0.5

  def __init__(self, verbose=False):
    if evdev is None:
      raise TypeError('KeyboardRecorderFromEvdev needs to be used on Linux ' +
                      '(or POSIX compatible) system. Instead, You can try it ' +
                      'on your console.')
    KeyboardRecorder.__init__(self, verbose)
    self.log('Input from evdev')
    keyboards = []
    ecode_ev_key = evdev.ecodes.ecodes['EV_KEY']
    ecode_key_esc = evdev.ecodes.ecodes['KEY_ESC']
    for device in [evdev.InputDevice(fn) for fn in evdev.list_devices()]:
      # TODO(shimazu): Consider more solid criteria to get 'regular' keyboards.
      if ecode_ev_key in device.capabilities() and \
         ecode_key_esc in device.capabilities()[ecode_ev_key]:
        keyboards.append(device)
    if len(keyboards) == 0:
      raise IOError('No keyboard found.')
    self._keyboards = keyboards
    for keyboard in keyboards:
      self.log('----')
      self.log(keyboard)
      self.log('name: {0}'.format(keyboard.name))
      self.log('phys: {0}'.format(keyboard.phys))
      self.log('repeat: {0}'.format(keyboard.repeat))
      self.log('info: {0}'.format(keyboard.info))
      self.log(keyboard.capabilities(verbose=True))

  def record(self):
    """
    Returns a tuple of |data| and |command|.
    |data|: an array of tuples of keys and time from the first character. None
            if the input is non-alphabet/numeric/symbols like ENTER, arrows etc.
    |command|: Commands like "KEY_ENTER" or None if |data| is valid.
    """
    start_time = None
    last_time = None
    data = []
    while True:
      # TODO(shimazu): Check inputs from all keyboards.
      event = self._keyboards[0].read_one()
      now = datetime.datetime.now()
      if last_time and (now - last_time).total_seconds() > self.WAIT_SECONDS:
        break
      if event is None:
        continue
      name = evdev.ecodes.bytype[event.type][event.code]
      ev_type = evdev.ecodes.EV[event.type]
      if ev_type != 'EV_KEY':
        continue
      # Keyboard input
      self.log('----')
      self.log(event)
      self.log('name: {}'.format(name))
      self.log('type: {}'.format(ev_type))
      # Check if the event is from releasing the button
      if event.value == 0:
        continue

      # It may be a non-alphabet/numeric/symbol key. Return it as a command.
      if event.code not in self.KEYS:
        if start_time is not None:
          continue
        return (None, name)
      last_time = now
      if start_time is None:
        start_time = now
      elapsed_ms = int((now - start_time).total_seconds() * 1000)
      data.append((self.KEYS[event.code], elapsed_ms))
    return (data, None)

InputSource = Enum('InputSource', 'EVDEV CONSOLE')

def create_keyboard_recorder(verbose=False, source=None):
  """Creates KeyboardRecorder.

  Args:
    verbose: Print the detail of input when it's true.
    source: InputSource.EVDEV, InputSource.CONSOLE or None (default)

  Returns:
    recorder: Corresponding KeyboardRecorder. If |source| is None, returns
      KeyboardRecorderFromConsole when stdin is attached to a console (isatty is
      true). Otherwise, returns KeyboardRecorderFromEvdev.
  """
  if source == InputSource.CONSOLE:
    return KeyboardRecorderFromConsole(verbose=verbose)
  if source == InputSource.EVDEV:
    return KeyboardRecorderFromEvdev(verbose=verbose)
  if sys.__stdin__.isatty():
    return KeyboardRecorderFromConsole(verbose=verbose)
  return KeyboardRecorderFromEvdev(verbose=verbose)

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

import serial
import struct

class Bluetooth():
  DEVICE_FILE = '/dev/serial0'
  BAUDRATE = 115200

  def __init__(self):
    try:
      self._conn = serial.Serial(self.DEVICE_FILE, self.BAUDRATE)
      self._dummy = False
      print('Bluetooth')
    except serial.SerialException:
      self._conn = None
      self._dummy = True
      print('Dummy Bluetooth')

  def send(self, string):
    """Send |string| as a series of characters. |string| should be
       alphabets, numbers and symbols which can be typed from your keyboard."""
    if self._dummy:
      print('bluetooth: {}'.format(string))
      return
    self._conn.write(string)

  # See http://ww1.microchip.com/downloads/en/DeviceDoc/bluetooth_cr_UG-v1.0r.pdf
  # for detail.
  UART_CODES = {
    'KEY_DELETE': 4,
    'KEY_RIGHT': 7,
    'KEY_BACKSPACE': 8,
    'KEY_ENTER': 10,
    'KEY_LEFT': 11,
    'KEY_DOWN': 12,
    'KEY_UP': 14,
  }

  def command(self, cmd):
    if cmd not in self.UART_CODES:
      print('Unknown Command: {}'.format(cmd))
      return
    if self._dummy:
      print('bluetooth: command({})'.format(cmd))
      return
    self.send(struct.pack('b', self.UART_CODES[cmd]))

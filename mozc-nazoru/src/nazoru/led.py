#!/usr/bin/env python
# -*- coding: utf-8 -*-
# vim: set fileencoding=utf-8 :
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

class LEDBase():
  def __init__(self, pin):
    self._pin = pin
  def on(self):
    pass
  def off(self):
    pass
  def blink(self, interval):
    pass

try:
  import RPi.GPIO as GPIO
  import threading

  class LED(LEDBase):
    ON = 'ON'
    OFF = 'OFF'

    def __init__(self, pin):
      GPIO.setmode(GPIO.BOARD)
      self._pin = pin
      self._lock = threading.Lock()
      self._timer = None
      GPIO.setup(pin, GPIO.OUT)
      self.off()

    def on(self):
      with self._lock:
        self._state = self.ON
        GPIO.output(self._pin, False)
        self._ensure_stop_timer()

    def off(self):
      with self._lock:
        self._state = self.OFF
        GPIO.output(self._pin, True)
        self._ensure_stop_timer()

    def blink(self, interval):
      self._ensure_stop_timer()
      def toggle():
        self._timer = None
        if self._state == self.ON:
          self.off()
        else:
          self.on()
        self._timer = threading.Timer(interval, toggle)
        self._timer.daemon = True
        self._timer.start()
      toggle()

    def _ensure_stop_timer(self):
      if self._timer is not None:
        self._timer.cancel()
        self._timer = None

except ImportError as e:
  import sys

  class LED(LEDBase):
    pass

LED_BLUE = LED(38)
LED_RED = LED(40)

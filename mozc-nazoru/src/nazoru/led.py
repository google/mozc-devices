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

class LEDBase(object):
  def __init__(self, pin):
    self._pin = pin
  def on(self):
    pass
  def off(self):
    pass
  def blink(self, interval):
    pass
  def set_brightness(self, brightness):
    pass

try:
  import RPi.GPIO as GPIO
  import threading
  GPIO.setmode(GPIO.BOARD)

  class LED(LEDBase):
    ON = 'ON'
    OFF = 'OFF'

    def __init__(self, pin):
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

  import wiringpi
  wiringpi.wiringPiSetupPhys()
  class SlowLED(LEDBase):
    DUTY_MAX = 1024
    INTERVAL_MS = 10

    def __init__(self, pin, delay_ms):
      self._pin = pin
      self._delay_ms = delay_ms
      wiringpi.pinMode(pin, wiringpi.GPIO.PWM_OUTPUT)
      self._target_duty = 0
      self._current_duty = 0
      self._remaining_cycles = 0
      self._lock = threading.Lock()
      self._timer = None
      self.off()

    # Called every 10ms
    def _update(self):
      with self._lock:
        diff = (self._target_duty - self._current_duty) // \
               self._remaining_cycles
        self._current_duty += diff
        self._remaining_cycles -= 1
        self._set_duty_immediate(self._current_duty)
        if self._remaining_cycles == 0:
          self._timer.cancel()
          self._timer = None
          return
        self._timer = threading.Timer(self.INTERVAL_MS * 0.001, self._update)
        self._timer.daemon = True
        self._timer.start()


    # |duty|: 0 - 100
    def _set_duty_immediate(self, duty):
      wiringpi.pwmWrite(self._pin, int(self.DUTY_MAX * duty // 100))

    def _set_duty_slow(self, duty, time_ms):
      with self._lock:
        self._target_duty = duty
        self._remaining_cycles = time_ms // self.INTERVAL_MS
        if self._timer is None:
          self._timer = threading.Timer(self.INTERVAL_MS * 0.001, self._update)
          self._timer.daemon = True
          self._timer.start()

    def on(self):
      self._set_duty_slow(100, self._delay_ms)

    def off(self):
      self._set_duty_slow(0, self._delay_ms)

    # |brightness|: 0 - 100
    def set_brightness(self, brightness):
      self._set_duty_slow(brightness, self._delay_ms)

except ImportError as e:
  import sys

  class LED(LEDBase):
    pass
  class SlowLED(LEDBase):
    def __init__(self, pin, delay_ms):
      super(SlowLED, self).__init__(pin)

LED_BLUE = LED(38)
LED_RED = LED(40)
LED_CHASSIS = SlowLED(32, 500)

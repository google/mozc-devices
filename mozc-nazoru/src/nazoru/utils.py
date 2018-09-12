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

import time
import sys

class Measure():
  def __init__(self, tag):
    self._tag = tag

  def __enter__(self):
    self._start = time.time()

  def __exit__(self, type, value, traceback):
    now = time.time()
    print('[{0}] {1} ms'.format(self._tag, (now - self._start)*1E3))

def clear_screen():
  sys.stdout.write('\033[2J')
  sys.stdout.write('\033[H')
  sys.stdout.flush()

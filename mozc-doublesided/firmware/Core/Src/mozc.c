// Copyright 2024 Google Inc.
// Use of this source code is governed by an Apache License that can be found in
// the LICENSE file.

#include "mozc.h"

#include <stdbool.h>
#include <stdio.h>

#include "i2c.h"
#include "main.h"

void mozc_init(void) { i2c_init(); }

void mozc_loop(void) { i2c_maybe_listen(); }

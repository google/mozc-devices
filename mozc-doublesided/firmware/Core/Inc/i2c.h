// Copyright 2024 Google Inc.
// Use of this source code is governed by an Apache License that can be found in
// the LICENSE file.

#ifndef I2C_H_
#define I2C_H_

#include <stdbool.h>

void i2c_init(void);
bool i2c_is_host(void);
void i2c_activate_host(void);
void i2c_maybe_listen(void);

#endif  // I2C_H_

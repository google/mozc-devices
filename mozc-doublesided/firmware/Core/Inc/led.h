// Copyright 2024 Google Inc.
// Use of this source code is governed by an Apache License that can be found in
// the LICENSE file.

#ifndef LED_H_
#define LED_H_

#include <stdint.h>

void led_set(uint8_t index, uint8_t r, uint8_t g, uint8_t b);
void led_flush(void);

#endif  // LED_H_
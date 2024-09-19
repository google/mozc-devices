// Copyright 2024 Google Inc.
// Use of this source code is governed by an Apache License that can be found in
// the LICENSE file.

#ifndef HID_H_
#define HID_H_

#include <stdint.h>

void hid_init(void);
void hid_update(const uint8_t* keys);
void hid_deinit(void);

#endif  // HID_H_

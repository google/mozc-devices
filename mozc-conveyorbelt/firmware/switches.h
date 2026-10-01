// Copyright 2026 Google Inc.
// Use of this source code is governed by an Apache License that can be found
// in the LICENSE file.

#ifndef __switch_h__
#define __switch_h__

#include <stdint.h>

void switches_init(void);
void switches_poll(uint8_t* report, uint8_t size);

#endif  // __switch_h__
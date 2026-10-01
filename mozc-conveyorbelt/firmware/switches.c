// Copyright 2026 Google Inc.
// Use of this source code is governed by an Apache License that can be found
// in the LICENSE file.

#include "switches.h"

#include <stdbool.h>

#include "ch559.h"
#include "gpio.h"
#include "keymap.h"

#define SHIFT_BITS 120
#define SHIFT_BYTES (SHIFT_BITS / 8)

static uint8_t switch_data[SHIFT_BYTES];

// Reads 'bits' number of bits into 'buffer'.
// Calling code must ensure 'buffer' has enough space (at least (bits + 7) / 8 bytes).
static void shift_register_read(uint8_t* buffer, uint16_t bits) {
  uint16_t bytes = (bits + 7) / 8;
  for (uint16_t i = 0; i < bytes; ++i) {
    buffer[i] = 0;
  }

  // 74HC166 SYNCHRONOUS load:
  // Set S/L (P2.2) LOW and pulse SCLK (P2.1) to latch parallel data across all cascaded ICs.
  digitalWrite(2, 2, LOW);   // S/L = LOW (Load mode)
  digitalWrite(2, 1, LOW);   // SCLK = LOW
  delayMicroseconds(5);
  digitalWrite(2, 1, HIGH);  // Pulse SCLK rising edge to trigger synchronous load!
  delayMicroseconds(5);
  digitalWrite(2, 1, LOW);
  digitalWrite(2, 2, HIGH);  // S/L = HIGH (Shift mode)
  delayMicroseconds(5);

  for (uint16_t i = 0; i < bits; ++i) {
    uint16_t byte_idx = i / 8;
    uint8_t bit_idx = 7 - (i % 8);

    if (digitalRead(2, 0) == HIGH) {
      buffer[byte_idx] |= (1 << bit_idx);
    }

    // Shift to next bit on SCLK rising edge
    if (i < bits - 1) {
      digitalWrite(2, 1, HIGH);
      delayMicroseconds(1);
      digitalWrite(2, 1, LOW);
      delayMicroseconds(1);
    }
  }
}

// Pin definitions on Port 2 for 8-bit Shift Register (74HC166 PISO Cascaded)
// P2.0: Data In (Q7 output from 74HC166 Pin 13)
// P2.1: SCLK (Serial Clock into 74HC166 Pin 6)
// P2.2: S/L (Shift / Synchronous Load into 74HC166 Pin 1)
void switches_init(void) {
  pinMode(2, 0, INPUT_PULLUP);
  pinMode(2, 1, OUTPUT);
  pinMode(2, 2, OUTPUT);

  digitalWrite(2, 1, LOW);   // SCLK initial LOW
  digitalWrite(2, 2, HIGH);  // S/L initial HIGH
}

void switches_poll(uint8_t* report, uint8_t size) {
  if (size < 2) {
    return;
  }

  // Read cascaded shift registers
  shift_register_read(switch_data, SHIFT_BITS);

  uint8_t key_max = size - 2;
  uint8_t modifiers = 0;
  bool shift_needed = false;
  uint8_t key_count = 0;

  for (uint8_t i = 0; i < key_max; i++) {
    report[2 + i] = 0;
  }

  // Check if Fn key (Byte 13, bit 0) is active
  bool fn_active = (switch_data[13] & 0x01) != 0;

  uint8_t idx = 0;
  for (uint8_t b = 0; b < SHIFT_BYTES; b++) {
    uint8_t byte_val = switch_data[b];
    for (uint8_t bit = 0; bit < 8; bit++, idx++) {
      if ((byte_val & (0x80 >> bit)) == 0) {
        continue;
      }

      const struct keymap_entry* entry = &keymap[idx];
      if (entry->keycode == KEY_NONE || entry->keycode == KEY_FN) {
        continue;
      }

      if (entry->shift) {
        shift_needed = true;
      }

      // Modifier key (0xE0..0xE7)
      if (entry->keycode >= KEY_LCTRL && entry->keycode <= 0xe7) {
        modifiers |= (1 << (entry->keycode - KEY_LCTRL));
        continue;
      }

      // Normal key
      uint8_t code = entry->keycode;
      if (fn_active) {
        if (code >= KEY_1 && code <= KEY_9) {
          code = KEY_F1 + (code - KEY_1);
        } else if (code == KEY_0) {
          code = KEY_F10;
        }
      }

      // Duplicate key prevention (e.g. 'a' and 'A' pressed simultaneously)
      bool duplicate = false;
      uint8_t check_len = (key_count < key_max) ? key_count : key_max;
      for (uint8_t k = 0; k < check_len; k++) {
        if (report[2 + k] == code) {
          duplicate = true;
          break;
        }
      }
      if (!duplicate) {
        if (key_count < key_max) {
          report[2 + key_count] = code;
        }
        key_count++;
      }
    }
  }

  if (shift_needed) {
    modifiers |= MOD_LSHIFT;
  }

  // Overflow: fill all key slots with ErrorRollOver
  if (key_count > key_max) {
    for (uint8_t i = 0; i < key_max; i++) {
      report[2 + i] = KEY_ERROR_ROLLOVER;
    }
  }

  report[0] = modifiers;
  report[1] = 0x00;
}
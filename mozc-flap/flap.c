/*
 * Copyright 2013 Google Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA  02110-1301, USA.
 */


/*
 * USB keyboard with a split flap display.
 *
 * PB0 through PB3: unipolar stepper motor control signals
 *  PB0 A
 *  PB1 ~A
 *  PB2 B
 *  PB3 ~B
 *
 * PB6: normally-open push switch for zero-position adjustment.
 * PB7: normally-open push switch for the input UI.
 */

#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>     /* for _delay_ms() */
#include "usb_keyboard.h"

// Number of flaps that appear in one cycle.
#define LETTERS 40

// Number of flaps for alphabets and numerical digits.
#define ALPHANUMERICS (26 + 10)
const uchar extra_character_keycodes[LETTERS - ALPHANUMERICS] = {
  KEYCODE_HYPHEN, KEYCODE_COMMA, KEYCODE_PERIOD, KEYCODE_SPACE
};

#define IDLE_TIMER_FREQUENCY 100
#define DELAY_BEFORE_INPUT (1 * IDLE_TIMER_FREQUENCY)
#define MAX_SPEED 9

#ifdef _FULL_STEP

#define STEPPER_PHASES 4
/* Stepper excitation pattern. Invert the order if necessary.
 * Bits 7 and 6 must be set to enable internal pullups for the switches.
 */
const uchar stepper_pattern[STEPPER_PHASES] = {0xc1, 0xc4, 0xc2, 0xc8};
#define STEPPER_PHASE_MASK 3
#define STEPS_PER_LETTER 5

#else

/* half-step mode */
#define STEPPER_PHASES 8
const uchar stepper_pattern[STEPPER_PHASES] = {
    0xc1, 0xc5, 0xc4, 0xc6, 0xc2, 0xca, 0xc8, 0xc9};
#define STEPPER_PHASE_MASK 7
#define STEPS_PER_LETTER 10

#endif

#define button_pressed() bit_is_clear(PINB, PINB7)
#define adjust_button_pressed() bit_is_clear(PINB, PINB6)

const unsigned int intervals[MAX_SPEED + 1] = {
  (unsigned int)(F_CPU / 8 / IDLE_TIMER_FREQUENCY),
  (unsigned int)(F_CPU / 8 / 25),
  (unsigned int)(F_CPU / 8 / 43),
  (unsigned int)(F_CPU / 8 / 56),
  (unsigned int)(F_CPU / 8 / 66),
  (unsigned int)(F_CPU / 8 / 75),
  (unsigned int)(F_CPU / 8 / 82),
  (unsigned int)(F_CPU / 8 / 90),
  (unsigned int)(F_CPU / 8 / 97),
  (unsigned int)(F_CPU / 8 / 103)
};

uchar stepper_phase = 0;

void advance_stepper_phase() {
#ifdef STEPPER_PHASE_MASK
  stepper_phase = (stepper_phase + 1) & STEPPER_PHASE_MASK;
#else
  stepper_phase ++;
  if (stepper_phase >= STEPPER_PHASES) {
      stepper_phase = 0;
  }
#endif
  PORTB = stepper_pattern[stepper_phase];
}

int __attribute__((noreturn)) main(void)
{
  DDRB = 0x3f;
  PORTB = stepper_pattern[stepper_phase];

  wdt_enable(WDTO_1S);

  initUsbKeyboard();

  uchar key = 0;
  uchar lastKey = 0;

  uchar character = 0;
  uchar substep = 0;
  uchar stop_count = 0;
  uchar speed = 0;
  enum {INIT, ACTIVE, PAUSED, ADJUST};
  uchar state = INIT;
  uchar on_count = 0;

  /* sets up timer for stepper interval */
  /* timer 1 CTC mode, counts up at f[clock]/8 [Hz] */
  TCCR1B = (1 << WGM12) | (1 << CS11);
  TCNT1 = 0;
  OCR1A = intervals[speed];

  while(1) {
    wdt_reset();
    usbPoll();

    if (bit_is_clear(TIFR, OCF1A)) {
      continue;
    }
    TIFR |= _BV(OCF1A);  /* clear OCF1A */

    switch(state) {
    case ADJUST:
      speed = 0;
      if (adjust_button_pressed()) {
      } else {
        state = INIT;
      }
      break;
    case INIT:
      if (button_pressed()) {
        speed = 1;
        on_count = 0;
        state = ACTIVE;
      }
      if (adjust_button_pressed()) {
        state = ADJUST;
        advance_stepper_phase();
        continue;
      }
      break;
    case ACTIVE:
      if (button_pressed()) {
        if (on_count < STEPS_PER_LETTER) {
          on_count ++;
        } else if (speed < MAX_SPEED) {
          speed ++;
        }
      } else {
        if (speed > 1) {
          speed --;
        } else if (speed == 1) {
          if (substep == 0) {
            speed = 0;
            stop_count = 0;
            state = PAUSED;
          }
        }
      }
      break;
    case PAUSED:
    default:
      if (button_pressed()) {
        speed = 1;
        state = ACTIVE;
      } else {
        if (stop_count == DELAY_BEFORE_INPUT) {
          if (character >= ALPHANUMERICS) {
            key = extra_character_keycodes[character - ALPHANUMERICS];
          } else {
            key = KEYCODE_A + character;
          }
          state = INIT;
        } else {
          stop_count ++;
        }
      }
    }

    OCR1A = intervals[speed];
    if (speed > 0) {
      substep ++;
      if (substep >= STEPS_PER_LETTER) {
        substep = 0;
        character ++;
        if (character >= LETTERS) {
          character = 0;
        }
      }
      advance_stepper_phase();
    }

    if (usbInterruptIsReady()) {
      if (key != lastKey) {
        lastKey = key;
        prepareInterruptReport(key);
        key = KEYCODE_NONE;
      }
    }
  }
}

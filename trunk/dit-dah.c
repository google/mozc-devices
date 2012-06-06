/*
 * Copyright 2012 Google Inc.
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
 * USB keyboard to input by Morse code with help of special romaji table.
 * The device transmits keycodes based on a single button input:
 *
 * "." for a short tap
 * "-" for a long tap
 * "/" for a pause after a tap
 * [SPACE][ENTER] for a long pause after taps (convert and commit)
 */

#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>     /* for _delay_ms() */
#include "usb_keyboard.h"

/*
 * Thresholds for button pressing duration.
 *
 * A counter is increased every 10 milliseconds in the main loop.
 * These time lengths are specified by the units of this counter.
 *
 * FYI: WPM = words per minute is commonly used unit of morse code speed.
 * 1 word stands for 50 dots. For example, 10 WPM means 1 dot=0.12s
 */

#define T_DIT 12                /* 10WPM */

/* minimum length of button press duration for a "dah" */
#define THRESHOLD_DIT_DAH (T_DIT + 7)

/* minimum length of time for a character separator */
#define THRESHOLD_GAP (T_DIT * 3)

/* length of time to wait before convert and commit */
#define THRESHOLD_LONG_GAP 100  /* 1 second */


#define EMPTY 255

int __attribute__((noreturn)) main(void)
{
  PORTB = 0xff;

  wdt_enable(WDTO_1S);
  initUsbKeyboard();

  /* sets up timer for button polling interval */
  /* timer 1 CTC mode, counts up at f[clock]/8 [Hz] */
  TCCR1B = (1 << WGM12) | (1 << CS11);
  TCNT1 = 0;
  OCR1A = (unsigned int)F_CPU / 8 * 100;  /* 100Hz, T=10 milliseconds */

  uchar key = 0;

  /* Keyboard keys to send.
   * Since we have only 1 byte buffer, the first key is dropped if the second
   * key is pushed before submitting it.
   */
  uchar cmdBuf = EMPTY;

  uchar state = 0;
  unsigned int count = 0;
  while(1) {  /* main event loop */
    wdt_reset();
    usbPoll();
    if(usbInterruptIsReady()) {
      if (cmdBuf != EMPTY) {
        prepareInterruptReport(cmdBuf);
        if (cmdBuf == KEYCODE_NONE) {
          cmdBuf = EMPTY;
        } else {
          /* release all keys */
          cmdBuf = KEYCODE_NONE;
        }
      }
    }
    /* samples the key input every 10 milliseconds to avoid chattering */
    if (bit_is_clear(TIFR, OCF1A)) {
      continue;
    }
    TIFR |= _BV(OCF1A);  /* clear OCF1A */

    key = bit_is_clear(PINB, PINB0);
    switch(state) {
    case 0:  /* initial state or after a long gap */
      if (key) {
        state = 1;
        count = 0;
      }
      break;
    case 1:  /* key is on */
      if (!key) {
        cmdBuf = KEYCODE_PERIOD;  /* dot */
        state = 3;
        count = 0;
        break;
      }
      if (count++ > THRESHOLD_DIT_DAH) {
        state = 2;
        count = 0;
      }
      break;
    case 2:  /* key has been pressed long enough to input dash */
      if (!key) {
        cmdBuf = KEYCODE_HYPHEN;  /* dash */
        state = 3;
        count = 0;
      }
      break;
    case 3:  /* key was released. */
      if (key) {
        state = 1;
        count = 0;
        break;
      }
      if (count++ > THRESHOLD_GAP) {
        cmdBuf = KEYCODE_SLASH;  /* word separator */
        state = 4;
      }
      break;
    case 4:  /* short gap, or long gap */
      if (key) {
        state = 1;
        count = 0;
        break;
      }
      if (count++ > THRESHOLD_LONG_GAP) {
        cmdBuf = KEYCODE_SPACE;  /* start conversion */
        state = 5;
        count = 0;
      }
      break;
    case 5:  /* long gap. pause before sending Enter key. */
      if (count++ > T_DIT) {
        cmdBuf = KEYCODE_ENTER;  /* commit conversion */
        state = 0;
        count = 0;
      }
      break;
    }
  }
}

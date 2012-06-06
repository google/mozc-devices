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
 * USB space key.
 * Connect a nomally-open switch to PB0. The device works as a space bar.
 */

#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>     /* for _delay_ms() */
#include "usb_keyboard.h"

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
  uchar lastKey = 0;

  while(1) {                /* main event loop */
    wdt_reset();
    usbPoll();

    /* samples the key input every 10 milliseconds to avoid chattering */
    if (bit_is_clear(TIFR, OCF1A)) {
      continue;
    }
    TIFR |= _BV(OCF1A);  /* clear OCF1A */

    if(usbInterruptIsReady()){
      key = bit_is_clear(PINB, PINB0) ? KEYCODE_SPACE : KEYCODE_NONE;
      if (key != lastKey) {
        lastKey = key;
        prepareInterruptReport(key);
      }
    }
  }
}

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

#include "usb_keyboard.h"

#include <avr/interrupt.h>  /* for sei() */
#include <avr/wdt.h>
#include <util/delay.h>     /* for _delay_ms() */

/* USB report descriptor, size must match usbconfig.h */
const PROGMEM char usbHidReportDescriptor[35] = {
  0x05, 0x01,            // USAGE_PAGE (Generic Desktop)
  0x09, 0x06,            // USAGE (Keyboard)
  0xa1, 0x01,            // COLLECTION (Application)
  0x05, 0x07,            //   USAGE_PAGE (Keyboard)
  0x19, 0xe0,            //   USAGE_MINIMUM (Keyboard LeftControl)
  0x29, 0xe7,            //   USAGE_MAXIMUM (Keyboard Right GUI)
  0x15, 0x00,            //   LOGICAL_MINIMUM (0)
  0x25, 0x01,            //   LOGICAL_MAXIMUM (1)
  0x75, 0x01,            //   REPORT_SIZE (1)
  0x95, 0x08,            //   REPORT_COUNT (8)
  0x81, 0x02,            //   INPUT (Data,Var,Abs)
  0x95, 0x01,            //   REPORT_COUNT (1)
  0x75, 0x08,            //   REPORT_SIZE (8)
  0x25, 0x65,            //   LOGICAL_MAXIMUM (101)
  0x19, 0x00,            //   USAGE_MINIMUM (Reserved (no event indicated))
  0x29, 0x65,            //   USAGE_MAXIMUM (Keyboard Application)
  0x81, 0x00,            //   INPUT (Data,Ary,Abs)
  0xc0                   // END_COLLECTION
};

static uchar reportBuffer[2];
static uchar idleRate;   /* repeat rate for keyboards */

#define MOD_CONTROL_LEFT    (1<<0)
#define MOD_SHIFT_LEFT      (1<<1)
#define MOD_ALT_LEFT        (1<<2)
#define MOD_GUI_LEFT        (1<<3)
#define MOD_CONTROL_RIGHT   (1<<4)
#define MOD_SHIFT_RIGHT     (1<<5)
#define MOD_ALT_RIGHT       (1<<6)
#define MOD_GUI_RIGHT       (1<<7)

uchar keyReport[2];

usbMsgLen_t usbFunctionSetup(uchar data[8])
{
  usbRequest_t *rq = (void *)data;

  /* The following requests are never used. But since they are required by
   * the specification, we implement them in this example.
   */
  if((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS) {
    /* class request type */
    /* wValue: ReportType (highbyte), ReportID (lowbyte) */
    if(rq->bRequest == USBRQ_HID_GET_REPORT) {
      /* we only have one report type, so don't look at wValue */
      usbMsgPtr = (void *)&reportBuffer;
      return sizeof(reportBuffer);
    } else if(rq->bRequest == USBRQ_HID_GET_IDLE) {
      usbMsgPtr = &idleRate;
      return 1;
    } else if(rq->bRequest == USBRQ_HID_SET_IDLE) {
      idleRate = rq->wValue.bytes[1];
    }
  } else {
    /* no vendor specific requests implemented */
  }
  /* default for not implemented requests: return no data back to host */
  return 0;
}

void initUsbKeyboard() {
  usbInit();
  /* enforce re-enumeration, do this while interrupts are disabled! */
  usbDeviceDisconnect();
  uchar i;
  i = 0;
  while(--i) {  /* fake USB disconnect for > 250 ms */
    wdt_reset();
    _delay_ms(1);
  }
  usbDeviceConnect();
  sei();
}

void prepareInterruptReport(uchar keycode) {
  reportBuffer[0] = 0;  /* modifier keys */
  reportBuffer[1] = keycode;
  /* called after every poll of the interrupt endpoint */
  usbSetInterrupt((void *)&reportBuffer, sizeof(reportBuffer));
}

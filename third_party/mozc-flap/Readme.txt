Copyright 2013 Google Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
MA  02110-1301, USA.


=====================================
 Summary
=====================================

Circuit diagram and firmware of split-flap display input device for
Google Japanese Input.


=====================================
 Files
=====================================

* V-USB library files
../third_party/usbdrv/

The directory and files were copied from V-USB files available at
http://www.obdev.at/vusb/

* Documents
COPYING ...... Open Source license for this software.
Readme.txt ... The file you are currently reading.

* Circuit diagram
circuit.png

* Firmware source codes
Makefile
flap.c
usbconfig.h
usb_keyboard.c
usb_keyboard.h


=====================================
 Building & Writing Firmware
=====================================

* Building firmware binaries

AVR-gcc is required.

$ make hex


* Writing to the program memory

Please refer documents of AVR programmer device you use.
Makefile contains "flash" rule that writes a hex file using Avrdude as an
example.


* Programming the fuse bits

Fuse bits must be configured in order to run the firmware correctly.

lower byte: 0xef
higher byte: 0xdb

# ATTiny2313 FUSE_L (Fuse low byte):
# 0xef = 1 1 1 0   1 1 1 1
#        ^ ^ \+/   \--+--/
#        | |  |       +------- CKSEL 3..0 (clock selection -> crystal @ 12 MHz)
#        | |  +--------------- SUT 1..0 (BOD enabled, fast rising power)
#        | +------------------ CKOUT (clock output on CKOUT pin -> disabled)
#        +-------------------- CKDIV8 (divide clock by 8 -> don't divide)
# ATTiny2313 FUSE_H (Fuse high byte):
# 0xdb = 1 1 0 1   1 0 1 1
#        ^ ^ ^ ^   \-+-/ ^
#        | | | |     |   +---- RSTDISBL (disable external reset -> enabled)
#        | | | |     +-------- BODLEVEL 2..0 (brownout trigger level -> 2.7V)
#        | | | +-------------- WDTON (watchdog timer always on -> disable)
#        | | +---------------- SPIEN (enable serial programming -> enabled)
#        | +------------------ EESAVE (preserve EEPROM on Chip Erase
#        |                               -> not preserved)
#        +-------------------- DWEN (debug wire enable)

Makefile contains "fuse" rule that programs fuse bits using Avrdude as an
example.


==================
 References
==================

The firmware and circuit diagram has been developed based on V-USB.

* V-USB
http://www.obdev.at/vusb/

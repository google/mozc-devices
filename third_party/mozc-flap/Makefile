#
# Copyright 2013 Google Inc.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
# MA  02110-1301, USA.
#


DEVICE  = attiny2313
F_CPU   = 12000000  # in Hz

AVRDUDE = avrdude -c usbasp -p $(DEVICE)  # edit this line for your programmer

USBDRV_DIR = ../third_party/usbdrv

CFLAGS  = -I$(USBDRV_DIR) -I. -DDEBUG_LEVEL=0


OBJECTS = $(USBDRV_DIR)/usbdrv.o $(USBDRV_DIR)/usbdrvasm.o $(USBDRV_DIR)/oddebug.o usb_keyboard.o flap.o

COMPILE = avr-gcc -Wall -Os -DF_CPU=$(F_CPU) $(CFLAGS) -mmcu=$(DEVICE)

FUSE_L  = 0xef
FUSE_H  = 0xdb
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
#        | +------------------ EESAVE (preserve EEPROM on Chip Erase -> not preserved)
#        +-------------------- DWEN (debug wire enable)


# symbolic targets:
help:
	@echo "This Makefile has no default rule. Use one of the following:"
	@echo "make hex ........... to build flap.hex"
	@echo "make program ....... to flash fuses and the flap firmware"
	@echo "make fuse .......... to flash the fuses"
	@echo "make flash ......... to flash the flap firmware"
	@echo "make clean ......... to delete objects and hex file"

hex: flap.hex

program: flash fuse

# rule for programming fuse bits:
fuse:
	@[ "$(FUSE_H)" != "" -a "$(FUSE_L)" != "" ] || \
		{ echo "*** Edit Makefile and choose values for FUSE_L and FUSE_H!"; exit 1; }
	$(AVRDUDE) -U hfuse:w:$(FUSE_H):m -U lfuse:w:$(FUSE_L):m

# rule for uploading firmware:
flash: flap.hex
	$(AVRDUDE) -U flash:w:flap.hex:i

# rule for deleting dependent files (those which can be built by Make):
clean:
	rm -f flap.{hex,lst,obj,cof,list,map,eep.hex,elf,s} $(OBJECTS) $(USBDRV_DIR)/oddebug.s $(USBDRV_DIR)/usbdrv.s

# Generic rule for compiling C files:
.c.o:
	$(COMPILE) -c $< -o $@

$(USBDRV_DIR)/usbdrvasm.o: $(USBDRV_DIR)/usbdrvasm.S \
   $(USBDRV_DIR)/usbportability.h $(USBDRV_DIR)/usbdrv.h \
   usbconfig.h $(USBDRV_DIR)/usbdrvasm12.inc \
   $(USBDRV_DIR)/asmcommon.inc

$(USBDRV_DIR)/oddebug.o: $(USBDRV_DIR)/oddebug.c $(USBDRV_DIR)/oddebug.h \
   $(USBDRV_DIR)/usbportability.h

$(USBDRV_DIR)/usbdrv.o: $(USBDRV_DIR)/usbdrv.c $(USBDRV_DIR)/usbportability.h \
   $(USBDRV_DIR)/usbdrv.h usbconfig.h $(USBDRV_DIR)/oddebug.h

usb_keyboard.o: usb_keyboard.c usb_keyboard.h $(USBDRV_DIR)/usbdrv.h \
    usbconfig.h $(USBDRV_DIR)/usbportability.h

flap.o: flap.c usbconfig.h usb_keyboard.h

# Generic rule for assembling Assembler source files:
.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@
# "-x assembler-with-cpp" should not be necessary since this is the default
# file type for the .S (with capital S) extension. However, upper case
# characters are not always preserved on Windows. To ensure WinAVR
# compatibility define the file type manually.

# Generic rule for compiling C to assembler, used for debugging only.
.c.s:
	$(COMPILE) -S $< -o $@

# file targets:

flap.elf: $(OBJECTS)
	$(COMPILE) -o flap.elf $(OBJECTS)

flap.hex: flap.elf
	rm -f flap.hex flap.eep.hex
	avr-objcopy -j .text -j .data -O ihex flap.elf flap.hex
	avr-size flap.hex

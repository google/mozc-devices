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

#include "usbdrv.h"

usbMsgLen_t usbFunctionSetup(uchar data[8]);
void initUsbKeyboard();
void prepareInterruptReport(uchar key);

#define KEYCODE_NONE      0x00
#define KEYCODE_A         0x04
#define KEYCODE_SPACE     0x2c
#define KEYCODE_PERIOD    0x37
#define KEYCODE_HYPHEN    0x2d
#define KEYCODE_SLASH     0x38
#define KEYCODE_ENTER     0x28
#define KEYCODE_SEMICOLON 0x33
#define KEYCODE_COMMA     0x36
#define KEYCODE_PERIOD    0x37

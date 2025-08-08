Copyright 2016 Google Inc.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.


Summary
=====================================

Circuit diagram and firmware of Google Japanese Input physical flick version.


Files
=====================================

* README.md  -- this file
* arduino/flick/*  -- firmware source code (Arduino sketch)
* circuit.png  -- circuit diagram
* photo/*  -- for reference


Building your device
=====================================

## Electronic parts

* Arduino Nano * 1
* RN-42-I/RM * 1
* SJoys 2-axis joystick module (Sainsmart) * 12
* MCP3208 * 3
* 0.1uF ceramic capacitor * 4
* 470 ohm resistor * 1
* 1k ohm resistor * 1
* Connectors

## RN42 configuration

This step is required for the first time, or when changing the device's name.
See Microchip's documents for detail.

1. Run a terminal emulator and open the serial port for Arduino.
2. Type '!' to enter pass-through mode.
3. Type '$$$'.
4. Configure the module by these commands:

* * * * * *
    SU,115k
    SM,6
    SA,2
    S~,6
    SH,0000
    SN,MY_PHYSICAL_FLICK_KEYBOARD
    R,1
* * * * * *
MY\_PHYSICAL\_FLICK\_KEYBOARD is a device name that will appear when you scan
Bluetooth devices, and can be replaced by your preferred name.

The commands will configure the module as follows:

* 115200bps
* Pairing mode
* SSP "just works" mode
* SPP profile
* HID flag register = 0 (keyboard)


Using flick input
=====================================

## Power supply

When operating the device, supply power by USB cables to Arduino Nano.

## Bluetooth pairing

Using your device (e.g. Android phone), scan Bluetooth devices and you will
find MY\_PHYSICAL\_FLICK\_KEYBOARD (or the name you set up) in the available
device list.

After pairing, find the device in the "physical keyboard" section and choose
"English - U.S." keyboard layout for it.

## How to input

Switch the Japanese IME on the paired device to romaji input mode.
Characters will be input as flick or press a key.

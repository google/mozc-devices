Copyright 2015 Google Inc.

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

Mechanical design, circuit diagram and firmware of Google Japanese Input
piropiro version.


 Files
=====================================

* arduino/piropiro/piropiro.ino -- firmware source code (Arduino sketch)
* stl/* -- 3D shape data of mechanical parts
* README.txt  -- this file
* assembly.png -- mechanical assembly instruction
* circuit.png -- circuit diagram
* example.jpg -- photograph of an example device


 Building your device
=====================================

## Mechanical parts

Output all mechanical parts under stl/ directory with a 3D printer.
Additionally, you need these parts.

* M2x4 scerws  x7
* M2 washer (inside diameter=2.2mm, outside diameter=5.8mm)  x1
* A party horn  x1

## Electronic parts

* Arduino Nano
    Some other models of Arduino (e.g. Arduino Uno) can be used
    if required function is available.
* RN-42-EK or a compatible evaluation kit
    RN-42 can be used instead if wired appropriately.
* GP2Y0E02A distance sensor
* 1/8W Resistors
    * 1k
    * 470
* Breadboard and jump wires

## Assembly

See the circuit diagram and mechanical assembly instruction images.

Also refer the example device in the photo.

## RN42 module configuration

This step is required for the first time, or when changing the device's name.
Note that you should not connect Arduino Nano when you configure RN-42-EK via
USB, because signal from Arduino Nano overrides the TxD signal on RN-42-EK.
See Microchip's documents for detail.

1. Connect RN-42-EK to your PC by USB.
2. Run a terminal emulator and open the serial port for RN-42-EK.
3. Type '$$$'. Make sure 'CMD' is returned from RN-42-EK and the green LED on
   RN-42-EK blinks fast.
4. Configure the module by these commands:

* * * * * *
    SU,115k
    SM,6
    SA,2
    S~,6
    SH,0000
    SN,MY_PIROPIRO_KEYBOARD
    R,1
* * * * * *
MY\_PIROPIRO\_KEYBOARD is a device name that will appear when you scan Bluetooth
devices, and can be replaced by your preferred name.

The commands will configure the module as follows:

* 115200bps
* Pairing mode
* SSP "just works" mode
* SPP profile
* HID flag register = 0 (keyboard)


 Using piropiro input
=====================================

## Power supply

When operating the device, supply power by USB cables to both RN-42-EK and
Arduino Nano. You can alternatively supply 3.3V power to RN-42-EK from Arduino's
3.3V pin, but this requires a modification on RN-42-EK to disconnect the
regulator's output pin on it from the circuit.

## Sensor adjustment

1. Attach the device to your party horn. The sensor should be positioned about
40mm apart from the rolled paper tube.
2. Turn on Arduino Nano and adjust the optical axis of the sensor. The LED on
Arduino board is lit while the sensor is collectly sensing the tip of the
paper tube between 50mm -- 350mm.

## Bluetooth pairing

Using your device (e.g. Android phone), scan Bluetooth devices and you will
find MY\_PIROPIRO\_KEYBOARD (or the name you set up) in the available device
list.

## How to input

Switch the Japanese IME on the paired device to romaji input mode.
Characters will be input as you blow the horn.
The length of the horn chooses the vowel.
In order to switch to the next column (consonant), quickly shrink the horn and blow it again.

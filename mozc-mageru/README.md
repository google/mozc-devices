# Gboard Spoon Bending Version

This contains programs, schematics and board layouts for Gboard Spoon Bending Version, which is released on **Apr 1, 2019**.

This is not an officially supported Google product.

# Contents

Directory structure is as follows.

- wireless/
  - firmware/
    - Firmware for the wireless version. (coming soon)
  - board/
    - Schematic and PCB layout made by EAGLE.
- wired/
  - firmware/
    - Arduino sketch for the wired version.
- ../third_party/mozc-mageru/spoon_stl/
   - Spoon shape data for 3D printing.

# Wired Version

## The spoon

Print the spoon under /third_party/mozc-mageru/spoon_stl/ using a 3D printer.
This is an example design of a flexible spoon that has a slot to embed a
flex sensor into.
We have tried it with PLA, but it will probably work with ABS as well.

## Electronic circuit

- Arduino Micro
- 22k-ohm resistor
- Flex sensor: FS-L-0055-253-ST (Spectra Symbol)

```
    Arduino Micro

         5V ---[22k ohm]-------+
                               |
         A5 -------------------+
                               |
        GND ---[Flex sensor]---+
```

## How to use the firmware

1. Open the sketch on Arduino IDE.
2. Choose "Arduino/Genuino Micro" in the [Tools]-[Board] menu.
3. If you are making Japanse-hiragana version, add ```#define JAPANESE_``` to the first line of the sketch
4. Upload to board.

## Sensor calibration

1. Open Serial Monitor.
2. (the home position, which decides when to commit a character)
   Bend the sensor slightly and send '0'. Make sure the LED turns off when the spoon is not bent by external force.
3. (the position for the first letter)
   Bend the sensor slightly a bit more and send '1'.
4. (the position for the last letter)
   Bend the sensor to the end and send '2'.
5. Send 'w' to save the configuration to EEPROM.

# Wireless Version

Coming soon.

# License

```
Licensed under the Apache License, Version 2.0 (the "License"); you may
not use this file except in compliance with the License. You may obtain
a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
```

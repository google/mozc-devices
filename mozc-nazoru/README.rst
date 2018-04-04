Gboard Physical Handwriting Version
===================================

.. image:: https://badge.fury.io/py/nazoru-input.svg
   :target: https://pypi.python.org/pypi/nazoru-input/
   :alt: PyPi

Gboard Physical Handwriting Version is a device which translates your
scribble on your keyboard into a character. You can make your own Gboard
Physical Handwriting Version by printing your own printed circuit board
(PCB). Also, you can train your own model to recognize a customized set
of characters. This repository provides circuit diagram, the board
layout and software to recognize your stroke over the keyboard as a
character.

Software Usage
--------------

Install and Try
~~~~~~~~~~~~~~~~

Please make sure your local environemnt has packages as follows.

For Ubuntu/Debian:

.. code:: shell

  $ sudo apt install libffi-dev libcairo2 # For Ubuntu/Debian

For macOS:

.. code:: shell

  $ brew install cairo  # For macOS

After that, you can try nazoru-input after installing it from pip.

.. code:: shell

   $ pip install nazoru-input
   $ nazoru-input

Using ``nazoru-input``, You can make your own machine into an
input device which accepts scribbles on the connected keyboard and send
characters via bluetooth. At the beginning, this script scans
connected keyboards and starts listening to inputs from one of the
keyboards. Then it translates a sequence of keydowns into a predicted
character considering pressed timings, and send the character to the
target device paired by bluetooth.

If you want to try it for development, you can download the source from
github and use ``-e`` option.

.. code:: shell

   $ sudo apt install libffi-dev libcairo2 # For Ubuntu/Debian
   $ git clone https://github.com/google/mozc-devices.git
   $ cd mozc-devices/mozc-nazoru
   $ pip install -e .
   $ nazoru-input

Training Model
~~~~~~~~~~~~~~

.. code:: shell

   $ curl -LO https://github.com/google/mozc-devices/raw/master/mozc-nazoru/data/strokes.zip
   $ nazoru-training ./strokes.zip

We have a script to generate a trained model which recognizes input
characters from scribbles. This script renders input stroke data into
images to extract useful features for prediction considering position of
the key and timing of keyboard events. Rendered images are fed into the
neural network model and the optimizer tunes the model to fit the data.
Once the training is done, the script outputs the trained graph, which
you can use for your own device. In the case where you install
``nazoru-training`` from pip, you can find ``strokes.zip`` at here:
https://github.com/google/mozc-devices/blob/master/mozc-nazoru/data/strokes.zip

You can change some configurations by passing command line flags (e.g.
path to the input/output files, hyper-parameters). Run
``nazoru-training --help`` for details.

Hardware Setup
--------------

Printed Circuit Board
~~~~~~~~~~~~~~~~~~~~~
Gboard Physical Handwriting Version uses Raspberry Pi Zero for the
keyboard input recognition and RN42 module for Bluetooth connection to
your laptop. You can check the wiring at ``board/schematic.png``. Also,
the original CAD data in EAGLE format is available
(``board/nazoru-stack.sch`` and ``board/nazoru-stack.brd``). The board
has non-connected pads and connectors for SPI and I2C. The connector
itself should be compatible with other Raspberry Pi, but we tested it
only on Raspberry Pi Zero W.

.. image:: https://raw.githubusercontent.com/google/mozc-devices/master/mozc-nazoru/board/schematic.png
   :width: 1000px

Raspberry Pi Setup
~~~~~~~~~~~~~~~~~~

**Step 0 - Prepare your Raspberry Pi**

Please prepare your Raspberry Pi, SD card initialized by RASPBIAN
image, and RN42 module. Connect your Raspberry Pi with RN42 as the
schematic shows. Please make sure you can have access to the internet
and also it has enough disk space to install packages on the following
steps.

**Step 1 - Setup UART to RN42**

If you try it on Raspberry Pi Zero W or Raspberry Pi 3, you need to
have additional settings for the serial communication because they
equipped a wireless module connected by the UART. See details at `an
official document
<https://www.raspberrypi.org/documentation/configuration/uart.md>`_.
In short, you need to add ``enable_uart=1`` to ``/boot/config.txt`` on
your Raspberry Pi.

**Step 2 - Initial setup for RN42**

You need to write your initial setup to RN42. At first, install screen
and open ``/dev/serial0`` for configuration.

.. code:: shell

  $ sudo apt install screen
  $ sudo screen /dev/serial0 115200

After that, please type the following commands. Note that you need to
type ENTER after input commands. For example, please type ``$$$``
and ENTER to execute ``$$$`` command.

1. ``$$$`` : Get into the command mode. The green LED will blink
   faster.
2. ``+`` : You can see what you type.
3. ``SD,0540`` : Set the device class to keyboard.
4. ``S~,6`` : Set the profile to HID.
5. ``SH,0200`` : Set the HID flag to keyboard.
6. ``SN,nazoru-input`` : Set the device name as nazoru-input. You
   can name it as you want.
7. ``R,1`` : Reboot RN42.

You can quit the screen by ``C-a k``.

**Step 3 - Download and install nazoru-input**

We provide a service file at ``data/nazoru.service`` to launch
``nazoru-input`` when booting. You can install it by uncomment
``data_files`` entry in ``setup.py``. Also, before installing this
package, We'd strongly recommend you to install some  package from apt
repository as follows, so that you can install pre-built packages.

.. code:: shell

  $ sudo apt install git python-pip python-numpy python-cairocffi \
    python-h5py python-imaging python-scipy libblas-dev liblapack-dev \
    python-dev libatlas-base-dev gfortran python-setuptools \
    python-html5lib
  $ sudo pip install http://ci.tensorflow.org/view/Nightly/job/nightly-pi-zero/219/artifact/output-artifacts/tensorflow-1.6.0-cp27-none-any.whl
  $ git clone https://github.com/google/mozc-devices
  $ cd mozc-devices/mozc-nazoru
  $ vi setup.py  # Remove '#' for data_files to install nazoru.service.
  $ sudo pip install . # If you want to develop nazoru-input, please use 'sudo pip install -e .' instead.

**Step 4 - Enjoy!**

.. code:: shell

  $ sudo nazoru-input # If you miss sudo, nazoru-input may use a DummyBluetooth object.

Training Data Format
--------------------

We are providing the raw training data at ``data/strokes.zip``. Once you
uncompress the zip file, you will get a ``.ndjson`` file which contains
all entries (we call them **strokes**) we have used for training.

Each stroke entry contains the following field:

+----------+-----------+-------------------------------------------+
| Key      | Type      | Description                               |
+==========+===========+===========================================+
| id       | integer   | A unique identifier across all strokes.   |
+----------+-----------+-------------------------------------------+
| writer   | string    | A unique identifier of writer.            |
+----------+-----------+-------------------------------------------+
| kana     | string    | Label of the character drawn.             |
+----------+-----------+-------------------------------------------+
| events   | list      | List of keyboard events.                  |
+----------+-----------+-------------------------------------------+

Each event is a 3-tuple of (``key``, ``event type``, ``time``). ``key``
describes the key on which the event happened. ``event type`` describes
what type of event happened. It should be "down" (keydown) or "up"
(keyup). ``time`` describes the consumed time until the event is fired
in millisecond.

For example, the entry below denotes a stoke of "ほ
(\\u307b)" accompanied with a sequence of keyboard events
starting from the keydown event on "t" and ending at the keyup event on
"l" which was fired 1.005 seconds later after it started recording.

.. code:: json

    {
      "id": 5788999721418752,
      "writer": "ffb0dac6b8be3faa81da320e29a2ba72",
      "kana": "\u307b",
      "events": [
        ["t", "down", 0],
        ["g", "down", 40],
        ...
        ["l", "down", 966],
        ["l", "up", 1005]
      ]
    }

You can also prepare your own dataset in ``.ndjson`` format and rebuild
the model on it. The list of kanas to recognize is in
``src/nazoru/lib.py``. You can update that if you want to modify the set
of characters.

Network Structure
-----------------

Data Preprocessing
~~~~~~~~~~~~~~~~~~

Each stroke entry is rendered to a square image before any training
runs. The script (``nazoru-training``) renders strokes in various ways
to extract useful features. Our default settings extract 10 features
from each stroke entry: 8 directional features and 2 temporal features
on 16x16 square canvas; this means that the input shape is 16x16x10 by
default.

Convolutional Network
~~~~~~~~~~~~~~~~~~~~~

Rendered inputs are fed into a convolutional neural network designed for
this task. Body structure looks like:

-  Convolutional layer (kernel size: 3x3, filter size: 32, stride: 2,
   activation: Relu)
-  Separatable convolutional layer (kernel size: 3x3, filter size: 64,
   stride: 1, activation: Relu)
-  Separatable convolutional layer (kernel size: 3x3, filter size: 128,
   stride: 2, activation: Relu)
-  Separatable convolutional layer (kernel size: 3x3, filter size: 128,
   stride: 1, activation: Relu)

For more details about the separatable convolutional layers, please
refer to `MobileNet <https://arxiv.org/abs/1704.04861>`__ architecture.

Authors
-------

Machine Learning:
Shuhei Iitsuka <tushuhei@google.com>

Hardwares, system setups:
Makoto Shimazu <shimazu@google.com>

License
-------

Licensed under the Apache License, Version 2.0 (the "License"); you may
not use this file except in compliance with the License. You may obtain
a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

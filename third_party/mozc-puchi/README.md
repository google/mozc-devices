Copyright 2017 Google Japan G.K.
	
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.


=====================================
 Summary
=====================================
やわらかな触感のGoogle日本語入力ぷちぷちバージョン。
読み込みができる据え付けタイプといつでもどこでも入力できるモバイルタイプのソースコードと造形データになります。

究極のGoogle日本語入力ツールで、ぬくもりと手触りのいい日本語入力をお楽しみください。
プチプチをつぶした時のにおいと一緒に「空気」も読むことができるでしょう。:-D

=====================================
Building your device
=====================================

![Photograph of the device](photo/device_desktop.jpg)

## Electronic parts

* Arduino Nano * 1
* Arduino Leonard * 1
* Microswitch * 6
* LED * 6
* Register *6

=====================================
 Files
=====================================
readme.md     ----> this file

License      ----> License file

*circuit
   circuit.jpg   ----> circuit for desktop/handheld puchi

*desktop
   +3Dprinter ----> data to print for 3D printer
          +desktop.igs
	      +desktop.stl
	      +desktop.stp

   +Arduino   ----> Arduino ino file to drive board (Leonard)
          +desktop.ino

*handheld
   +3Dprinter ----> data to print for 3D printer
          +handheld.igs
	      +handheld.stl
	      +handheld.stp
   +Arduino   ----> Arduino ino file to drive board (Arduino mini)
          +handheld.ino


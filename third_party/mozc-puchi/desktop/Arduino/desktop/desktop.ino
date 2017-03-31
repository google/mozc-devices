/*
Copyright 2017 Google Inc.
	
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <Wire.h>
#include <Keyboard.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

#define SW_1 1
#define SW_2 18
#define SW_3 19
#define SW_4 4
#define SW_5 5
#define SW_6 6

#define LED_1 8
#define LED_2 9
#define LED_3 10
#define LED_4 11
#define LED_5 12
#define LED_6 13

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 2);

/*グローバル変数設定*/
int i;
int key_phase;//キーボードのどの位置を読み取っているか
/*初期設定*/
void setup() {

  /*スイッチ設定*/
  pinMode(SW_1, INPUT_PULLUP);
  pinMode(SW_2, INPUT_PULLUP);
  pinMode(SW_3, INPUT_PULLUP);
  pinMode(SW_4, INPUT_PULLUP);
  pinMode(SW_5, INPUT_PULLUP);
  pinMode(SW_6, INPUT_PULLUP);

  /*LED設定*/
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(LED_5, OUTPUT);
  pinMode(LED_6, OUTPUT);

  /*シリアル設定*/
  Serial.begin(9600);

  AFMS.begin();

  myMotor->setSpeed(300);  // 100 rpm
  /*キーボード設定*/
  Keyboard.begin();
}

void loop() {
  myMotor->step(1, FORWARD, INTERLEAVE);  //ローラーを送る

  /*各スイッチの状態をLEDで表示*/
  /*SW_6読み取り*/
  if (digitalRead(SW_6) == 0) { //SW_6が反応している場合
    digitalWrite(LED_6, HIGH);
  } else {
    digitalWrite(LED_6, LOW);
  }

  /*SW_1読み取り*/
  if (digitalRead(SW_1) == 0) { //SW_1が反応している場合
    digitalWrite(LED_1, HIGH);
  } else {
    digitalWrite(LED_1, LOW);
  }

  /*SW_2読み取り*/
  if (digitalRead(SW_2) == 0) { //SW_2が反応している場合
    digitalWrite(LED_2, HIGH);
  } else {
    digitalWrite(LED_2, LOW);
  }

  /*SW_3読み取り*/
  if (digitalRead(SW_3) == 0) { //SW_3が反応している場合
    digitalWrite(LED_3, HIGH);
  } else {
    digitalWrite(LED_3, LOW);
  }

  /*SW_4読み取り*/
  if (digitalRead(SW_4) == 0) { //SW_4が反応している場合
    digitalWrite(LED_4, HIGH);
  } else {
    digitalWrite(LED_4, LOW);
  }

  /*SW_5読み取り*/
  if (digitalRead(SW_5) == 0) { //SW_5が反応している場合
    digitalWrite(LED_5, HIGH);
  } else {
    digitalWrite(LED_5, LOW);
  }

  /*ここからキー入力処理*/
  /*SW_6はキーボードの位置を確認する役割*/
  if (digitalRead(SW_1) == key_phase % 2) { //SW_6の入力が変化した場合
    if (key_phase % 2 == 0) { //key_phaseが偶数の場合
      //SW_2とSW_4を読み取る

      /*SW_2の読取*/
      if (digitalRead(SW_4)) {
        switch (key_phase) {
          case 2:
            Keyboard.print("a");
            break;
          case 4:
            Keyboard.print("s");
            break;
          case 6:
            Keyboard.print("d");
            break;
          case 8:
            Keyboard.print("f");
            break;
          case 10:
            Keyboard.print("g");
            break;
          case 12:
            Keyboard.print("h");
            break;
          case 14:
            Keyboard.print("j");
            break;
          case 16:
            Keyboard.print("k");
            break;
          case 18:
            Keyboard.print("l");
            break;
          case 20:
            Keyboard.print(";");
            break;
          case 22:
            Keyboard.print(":");
            break;
            //          default:
            //            Keyboard.print("Error");
            //            key_phase = 0;
            //            break;
        }
      }

      /*SW_4の読取*/
      if (digitalRead(SW_2)) {
        switch (key_phase) {
          case 0:
            Keyboard.print("1");
            break;
          case 2:
            Keyboard.print("2");
            break;
          case 4:
            Keyboard.print("3");
            break;
          case 6:
            Keyboard.print("4");
            break;
          case 8:
            Keyboard.print("5");
            break;
          case 10:
            Keyboard.print("6");
            break;
          case 12:
            Keyboard.print("7");
            break;
          case 14:
            Keyboard.print("8");
            break;
          case 16:
            Keyboard.print("9");
            break;
          case 18:
            Keyboard.print("0");
            break;
          case 20:
            Keyboard.print("-");
            break;
          case 22:
            Keyboard.print("^");
            break;
          case 24:
            Keyboard.print("\\");
            break;
            //          default:
            //            Keyboard.print("Error");
            //            key_phase = 0;
            //            break;
        }
      }

    } else { //key_phaseが奇数の場合
      //SW_1とSW_3読み取る

      /*SW_1の読取*/
      if (digitalRead(SW_5)) {
        switch (key_phase) {
          case 3:
            Keyboard.print("z");
            break;
          case 5:
            Keyboard.print("x");
            break;
          case 7:
            Keyboard.print("c");
            break;
          case 9:
            Keyboard.print("v");
            break;
          case 11:
            Keyboard.print("b");
            break;
          case 13:
            Keyboard.print("n");
            break;
          case 15:
            Keyboard.print("m");
            break;
          case 17:
            Keyboard.print(",");
            break;
          case 19:
            Keyboard.print(".");
            break;
          case 21:
            Keyboard.print("/");
            break;
          case 23:
            Keyboard.print("\\");
            break;
            //          default:
            //            Keyboard.print("Error");
            //            key_phase = 0;
            //            break;
        }
      }

      /*SW_3の読取*/
      if (digitalRead(SW_3)) {
        switch (key_phase) {
          case 1:
            Keyboard.print("q");
            break;
          case 3:
            Keyboard.print("w");
            break;
          case 5:
            Keyboard.print("e");
            break;
          case 7:
            Keyboard.print("r");
            break;
          case 9:
            Keyboard.print("t");
            break;
          case 11:
            Keyboard.print("y");
            break;
          case 13:
            Keyboard.print("u");
            break;
          case 15:
            Keyboard.print("i");
            break;
          case 17:
            Keyboard.print("o");
            break;
          case 19:
            Keyboard.print("p");
            break;
          case 21:
            Keyboard.print("@");
            break;
            //          default:
            //            Keyboard.print("Error");
            //            key_phase = 0;
            //            break;
        }
      }
    }
    key_phase++;
    delay(20);
  }
  if (key_phase > 24) { //すべてのキー入力が終了
    key_phase = 0;
    delay(100);
    for (i = 0; i < 3; i++) {
      digitalWrite(LED_1, HIGH);
      digitalWrite(LED_2, HIGH);
      digitalWrite(LED_3, HIGH);
      digitalWrite(LED_4, HIGH);
      digitalWrite(LED_5, HIGH);
      digitalWrite(LED_6, HIGH);
      delay(300);
      digitalWrite(LED_1, LOW);
      digitalWrite(LED_2, LOW);
      digitalWrite(LED_3, LOW);
      digitalWrite(LED_4, LOW);
      digitalWrite(LED_5, LOW);
      digitalWrite(LED_6, LOW);
      delay(300);
    }
  }
}

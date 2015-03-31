/*
 * Copyright 2015 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Firmware of piropiro (party horn) Bluetooth keyboard.
 */

#define V_REF 5.0
#define PIN_LED 13
#define N_AD_SAMPLES 10

#define INTERVAL_MSEC 20
#define COMMIT_TIME (600 / INTERVAL_MSEC)

#define ROWS 5
#define COLS 9

const char* characters[ROWS * COLS] = {
  "a", "i", "u", "e", "o",
  "ka", "ki", "ku", "ke", "ko",
  "sa", "si", "su", "se", "so",
  "ta", "ti", "tu", "te", "to",
  "na", "ni", "nu", "ne", "no",
  "ha", "hi", "hu", "he", "ho",
  "ma", "mi", "mu", "me", "mo",
  "ya", "ya", "yu", "yu", "yo",
  "wa", "wo", "nn", ",", "."
};

int column = 0;
int vowel = 0;
int release_duration = 0;

void setup() {
  Serial.begin(115200);
  pinMode(PIN_LED, OUTPUT);
  column = 0;
  vowel = 0;
}

float getVoltage(int ch) {
  return analogRead(ch) * V_REF / 1023;
}

float getAverageVoltage(int ch) {
  float sum = 0.0;
  for (int i = 0; i < N_AD_SAMPLES; i++) {
    sum += getVoltage(ch);
  }
  return sum / N_AD_SAMPLES;
}

float voltageToLength(float voltage) {
  return 648 - voltage * 268;
}

void loop() {
  float length = voltageToLength(getAverageVoltage(0));
  if (length > 350) {
    digitalWrite(PIN_LED, LOW);
  } else {
    digitalWrite(PIN_LED, HIGH);
    if (length < 50) {
      if (vowel > 0) {
        vowel = 0;
        column ++;
        if (column >= COLS) {
          column = 0;
        }
        release_duration = 0;
      } else if (release_duration > COMMIT_TIME) {
        vowel = 0;
        column = 0;
      } else if (column > 0) {
        release_duration ++;
      }
    } else {
      int target_vowel = (length - 80) / 40 + 1;
      if (target_vowel > 5) target_vowel = 5;
      if (vowel < target_vowel) {
        if (column > 0 || vowel > 0) {
          Serial.print("\b");
        }
        vowel ++;
        int current_character = vowel - 1 + column * 5;
        Serial.print(characters[current_character]);
      }
    }
  }
  delay(INTERVAL_MSEC);
}


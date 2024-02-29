//
// Copyright 2019 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <Keyboard.h>
#include <avr/eeprom.h>

#ifdef JAPANESE_

// Japanese (hiragana) mode. Must be used with romaji input mode.
#define ROWS 5
#define COLS 10
#define N_KEYS (ROWS * COLS)

// clang-format off
const char* characters[N_KEYS] = {
    "a", "i", "u", "e", "o",
    "ka", "ki", "ku", "ke", "ko",
    "sa", "si", "su", "se", "so",
    "ta", "ti", "tu", "te", "to",
    "na", "ni", "nu", "ne", "no",
    "ha", "hi", "hu", "he", "ho",
    "ma", "mi", "mu", "me", "mo",
    "ya", "ya", "yu", "yu", "yo",
    "ra", "ri", "ru", "re", "ro",
    "wa", "wo", "nn", ",", "."
};
// clang-format on

#else

// English alphabet mode.
#define N_KEYS 27
const char* characters[N_KEYS] = {"a", "b", "c", "d", "e", "f", "g", "h", "i",
                                  "j", "k", "l", "m", "n", "o", "p", "q", "r",
                                  "s", "t", "u", "v", "w", "x", "y", "z", " "};

#endif

const int kAnalogInPin = A5;
const int kLedPin = 13;
const uint8_t kMagicNumber = 0xa5;

// Decay ratio of the low-pass filter for smoothing the sensor input.
// Between 0.0 and 1.0.
const float kFilterDecay = 0.9;

struct Configuration {
  int min;
  int max;
  int home;
};

Configuration config;
float filtered = 0;
float max_bend = 0;
int prev_key = 0;
bool active = false;
bool enable_key_output = true;

void LoadDefaultConfig() {
  config.min = 612;
  config.max = 757;
  config.home = 580;
}

void setup() {
  Serial.begin(115200);
  Keyboard.begin();
  LoadConfig();
  pinMode(kLedPin, OUTPUT);
  digitalWrite(kLedPin, LOW);
}

void OutputKey(const char* str) {
  if (!enable_key_output) {
    Serial.print(str);
    return;
  }
  Keyboard.print(str);
}

uint8_t Checksum(uint8_t initial_value, void* data, size_t size) {
  uint8_t result = initial_value;
  for (size_t i = 0; i < size; i++) {
    result += ((uint8_t*)data)[i];
  }
  return result;
}

void SaveConfig() {
  eeprom_write_block(&config, (void*)0, sizeof(config));
  int8_t checksum = Checksum(kMagicNumber, &config, sizeof(config));
  eeprom_write_block(&checksum, sizeof(config), 1);
}

void LoadConfig() {
  eeprom_read_block(&config, (void*)0, sizeof(config));
  uint8_t checksum_in_eeprom;
  eeprom_read_block(&checksum_in_eeprom, sizeof(config), 1);
  if (Checksum(kMagicNumber, &config, sizeof(config)) != checksum_in_eeprom) {
    Serial.print("No data in EEPROM. Loading default config.");
    LoadDefaultConfig();
  }
  Serial.print("home=");
  Serial.print(config.home);
  Serial.print(" min=");
  Serial.print(config.min);
  Serial.print(" max=");
  Serial.println(config.max);
}

void loop() {
  int sensor_value = analogRead(kAnalogInPin);
  float normalized_bend =
      (sensor_value - config.min) / (float)(config.max - config.min);
  filtered = (filtered * kFilterDecay + normalized_bend * (1 - kFilterDecay));
  if (Serial.available()) {
    int key = Serial.read();
    switch (key) {
      // Sensor calibration commands.
      case '0':
        config.home = sensor_value;
        break;
      case '1':
        config.min = sensor_value;
        break;
      case '2':
        config.max = sensor_value;
        break;
      case 'w':
        SaveConfig();
        break;
      case 'r':
        LoadConfig();
        break;

      // Other debug commands.
      case '!':
        enable_key_output = !enable_key_output;
        break;
      case ' ':
        // Show sensor status for debugging.
        Serial.print(sensor_value);
        Serial.print("\t");
        Serial.print(normalized_bend);
        Serial.print("\t");
        Serial.print(filtered);
        Serial.println();
    }
  }
  if (sensor_value < config.home && active) {
    active = false;
    filtered = 0;
    max_bend = 0;
  } else if (filtered > 0) {
    max_bend = max(max_bend, filtered);
    int new_key = min(N_KEYS - 1, (int)(max_bend * N_KEYS));
    if (new_key != prev_key) {
      if (active) {
        OutputKey("\b");
      }
      OutputKey(characters[new_key]);
      prev_key = new_key;
    }
    active = true;
  }
  digitalWrite(kLedPin, active);
  delay(2);
}

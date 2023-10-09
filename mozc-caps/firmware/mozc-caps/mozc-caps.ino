#include <BleKeyboard.h>
#include <M5StickCPlus.h>

#include "imu.h"

// Comment out the line below to use English alphabet mode.
#define JAPANESE_

#ifdef JAPANESE_
// Japanese (hiragana) mode. Must be used with romaji input mode.

// clang-format off
const char* characters[] = {
  "a", "i", "u", "e", "o",
  "ka", "ki", "ku", "ke", "ko",
  "ga", "gi", "gu", "ge", "go",
  "sa", "si", "su", "se", "so",
  "za", "zi", "zu", "ze", "zo",
  "ta", "ti", "tu", "te", "to",
  "da", "di", "du", "de", "do",
  "na", "ni", "nu", "ne", "no",
  "ha", "hi", "hu", "he", "ho",
  "ba", "bi", "bu", "be", "bo",
  "pa", "pi", "pu", "pe", "po",
  "ma", "mi", "mu", "me", "mo",
  "ya", "yu", "yo",
  "ra", "ri", "ru", "re", "ro",
  "wa", "wo", "nn",
  "lya", "lyu", "lyo", "ltu",
  "-",
};
// clang-format on

#else

// English alphabet mode.

const char* characters[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i",
                            "j", "k", "l", "m", "n", "o", "p", "q", "r",
                            "s", "t", "u", "v", "w", "x", "y", "z", " "};

#endif

// A class that handles character input, interactively showing
// unsettled characater on the target device.
class Compositor {
 public:
  Compositor() : last_character_unsettled_(false) {}
  // Commit the current composition by sending a newline character.
  void commit() {
      if (last_character_unsettled_) {
          bleKeyboard.write('\n');
          last_character_unsettled_ = false;
      }
  }
  void enter();
  void select(const char* str);

 private:
  bool last_character_unsettled_;
};

const float kSamplingFrequency = 100.;
const float kIntervalMicros = 1e6 / kSamplingFrequency;
const uint8_t PUSH_SW = G33;

BleKeyboard bleKeyboard("mozc-caps");
M5StackIMUManager imu;
Compositor compositor;
long last_time_micros;
float yaw_origin = 180;
int current_key = 0;
int last_key = 0;

void Compositor::enter() {
  if (!last_character_unsettled_) {
    return;
  }
  last_character_unsettled_ = false;
}

void Compositor::select(const char* str) {
  if (last_character_unsettled_) {
    // It is assumed there is only one unsettled character,
    // as the IME should be set to the romaji input mode.
    bleKeyboard.write('\b');
  }
  for (const char* p = str; *p; p++) {
    bleKeyboard.write(*p);
  }
  last_character_unsettled_ = true;
}

void setup() {
  M5.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(BLACK);
  imu.Init();
  last_time_micros = micros();
  pinMode(PUSH_SW, INPUT_PULLUP);
  bleKeyboard.begin();
}

void loop() {
  float gyro_x, gyro_y, gyro_z, acc_x, acc_y, acc_z;
  M5.IMU.getGyroData(&gyro_x, &gyro_y, &gyro_z);
  M5.IMU.getAccelData(&acc_x, &acc_y, &acc_z);
  // Convert coordinate system to use the rotation around the Y axis as "yaw"
  // angle.
  imu.Update(kSamplingFrequency, gyro_z, gyro_y, -gyro_x, acc_z, acc_y, -acc_x);
  float pitch, roll, yaw;
  imu.GetAHRSData(&pitch, &roll, &yaw);

  M5.update();
  if (M5.BtnA.wasPressed()) {
    yaw_origin = yaw;
  }
  if (M5.BtnA.pressedFor(1000)) {
    imu.Init();
  }

  float relative_angle = yaw - yaw_origin;
  if (relative_angle > 180) {
    relative_angle -= 360;
  } else if (relative_angle < -180) {
    relative_angle += 360;
  }

  bool key_pressed = false;
  if (digitalRead(PUSH_SW) == LOW) {
    key_pressed = true;
  }

  // The range of rotation angle [deg] from the center, used for selecting
  // characters.
  const float kAngleRange = 80;
  int num_keys = sizeof(characters) / sizeof(characters[0]);
  float position = (relative_angle + kAngleRange) / kAngleRange / 2 * num_keys;
  int key_index = static_cast<int>(position + 0.5);
  if (key_index < 0) key_index = 0;
  if (key_index > num_keys - 1) key_index = num_keys - 1;
  float residual = position - key_index;
  if (residual < -0.5) residual += 1;
  if (residual > 0.5) residual -= 1;
  if (residual < 0) {
    residual = -residual;
  }
  if (residual < 0.4 && !key_pressed) {
    current_key = key_index;
    if (current_key != last_key) {
      compositor.select(characters[current_key]);
    }
    last_key = current_key;
  }
  if (key_pressed) {
    compositor.enter();
  }

  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(OLIVE, 0x000000);
  M5.Lcd.setCursor(30, 110);
  if (imu.Ready()) {
    M5.Lcd.printf("                           ");
  } else {
    M5.Lcd.printf("calibrating gyro sensors...");
  }

  M5.Lcd.setTextSize(7);
  M5.Lcd.setCursor(0, 24);
  M5.Lcd.setTextColor(key_pressed ? YELLOW : DARKGREEN, 0x000000);
  M5.Lcd.printf(" %3s ", characters[current_key]);

  long next_time_micros = last_time_micros + kIntervalMicros;
  while (micros() < next_time_micros) {
    delay(1);
  }
  last_time_micros = next_time_micros;
}

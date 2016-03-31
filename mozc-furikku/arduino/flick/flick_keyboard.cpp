#include "flick_keyboard.h"
#include <stdint.h>

#define ADC_BITS 12

void FlickKeyboard::ProcessSensorData(const SensorData& data, size_t maxKeyNum,
    const char** outputStrings, int* nOutputs) {
  const char* characters[COLS][ROWS] = {
    {"a", "i", "u", "e", "o"},
    {"ka", "ki", "ku", "ke", "ko"},
    {"sa", "si", "su", "se", "so"},
    {"ta", "ti", "tu", "te", "to"},
    {"na", "ni", "nu", "ne", "no"},
    {"ha", "hi", "hu", "he", "ho"},
    {"ma", "mi", "mu", "me", "mo"},
    {"ya", "(", "yu", ")", "yo"},
    {"ra", "ri", "ru", "re", "ro"},
    {"\n", "\b", "", " ", ""},
    {"wa", "wo", "nn", "-", "~"},
    {",", ".", "?", "!", "..."}
  };
  *nOutputs = 0;
  for (size_t i = 0; i < COLS; i++) {
    Direction s = ConvertToFlickState(data.axes[i * 2 + 1],
        data.axes[i * 2], data.button[i]);
    if (lastState[i] == NONE && s != NONE) {
      if (*nOutputs < maxKeyNum) {
        outputStrings[(*nOutputs)++] = characters[i][s];
      }
    }
    lastState[i] = s;
  }
}

FlickKeyboard::FlickKeyboard() {
  for (size_t i = 0; i < COLS; i++) {
    lastState[i] = NONE;
  }
}

Direction FlickKeyboard::ConvertToFlickState(
    int16_t x, int16_t y, bool buttonPressed) {
  const int16_t adScale = 1 << ADC_BITS;
  const int16_t adCenter = adScale / 2;
  const int16_t threshold = adScale * 0.4;

  int16_t diffX = x - adCenter;
  int16_t diffY = y - adCenter;
  if (buttonPressed) {
    return CENTER;
  }
  if (abs(diffX) > abs(diffY)) {
    if (diffX < -threshold) {
      return LEFT;
    } else if (diffX > threshold) {
      return RIGHT;
    }
  } else {
    if (diffY < -threshold) {
      return UP;
    } else if (diffY > threshold) {
      return DOWN;
    }
  }
  return NONE;
}


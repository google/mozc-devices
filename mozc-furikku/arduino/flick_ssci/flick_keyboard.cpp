#include "flick_keyboard.h"
#include <stdint.h>

void FlickKeyboard::ProcessSensorData(const SensorData& data, size_t maxKeyNum,
                                      const char** outputStrings, int* nOutputs) {
  const int kButtonSwapTable[COLS] = {8, 4, 0, 9, 5, 1, 10, 6, 2, 11, 7, 3, 12, 13, 14, 15, 16, 17, 18, 19};
  const int kAxesSwapTable[COLS] =   {0, 4, 8, 1, 5, 9, 2, 6, 10, 3, 7, 11, 12, 13, 14, 15, 16, 17, 18, 19};
  const char* characters[COLS][ROWS] = {
    {"a", "i", "u", "e", "o"},      // Joystick
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
    {",", ".", "?", "!", "..."},
    {"\x08", "", "", "", ""},       // Tact switch
    {"\x07", "", "", "", ""},
    {" ", "", "", "", ""},
    {"\x10", "", "", "", ""},
    {"", "", "", "", ""},
    {"\x11", "", "", "", ""},
    {"", "", "", "", ""},
    {"", "", "", "", ""}
  };
  *nOutputs = 0;
  for (size_t i = 0; i < COLS; i++) {
    Direction s = ConvertToFlickState(data.axes[kAxesSwapTable[i] * 2], data.axes[kAxesSwapTable[i] * 2 + 1], data.button[kButtonSwapTable[i]]);
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

Direction FlickKeyboard::ConvertToFlickState(int16_t x, int16_t y, bool buttonPressed) {
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
      return RIGHT;
    } else if (diffX > threshold) {
      return LEFT;
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


#pragma once

#include <stdint.h>
#include <stdlib.h>

#define ROWS 5
#define COLS 20  // Equals to the number of the keys.

enum Direction {
  CENTER, LEFT, UP, RIGHT, DOWN, NONE
};

struct SensorData {
  uint16_t axes[COLS * 2];
  bool button[COLS];
};

class FlickKeyboard {
 private:
  Direction lastState[COLS];
  Direction ConvertToFlickState(int16_t x, int16_t y,
      bool buttonPressed);
 public:
  FlickKeyboard();
  void ProcessSensorData(const SensorData& data, size_t maxKeyNum,
      const char** outputStrings, int* nOutputs);
};


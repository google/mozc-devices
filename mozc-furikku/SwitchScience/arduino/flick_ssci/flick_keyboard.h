#pragma once

#include <stdint.h>
#include <stdlib.h>

#define ROWS 5          // a i u e o
#define COLS 20         // Equals to the number of the keys.
#define FLICKS 12       // Equals to the number of the flick keys.
#define ADC_BITS 10     // The number of A/D convertor bit width

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


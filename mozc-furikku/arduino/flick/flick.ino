#include <SPI.h>
#include "flick_keyboard.h"

// Number of A/D converter ICs.
const int kNumAdcIc = 3;
const int kCsPins[kNumAdcIc] = {10, 9, 8};

const int kButtonPins[12] = {
  // If you use Arduino Nano version 2, use A6 and A7 instead of A0 and A1.
  // (which are actually port C, thus used as digital input)
  A0, A1, A2, A3, A4, A5,
  7, 6, 5, 4, 3, 2
};

FlickKeyboard keyboard;

void setup() {
  Serial.begin(115200);
  for (size_t i = 0; i < kNumAdcIc; i++) {
    pinMode(kCsPins[i], OUTPUT);
    digitalWrite(kCsPins[i], HIGH);
  }
  for (size_t i = 0; i < 12; i++) {
    pinMode(kButtonPins[i], INPUT_PULLUP);
  }
  SPI.begin();
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
}

void SelectChip(uint8_t id) {
  if (id > kNumAdcIc) {
    return;
  }
  for (size_t i = 0; i < kNumAdcIc; i++) {
    digitalWrite(kCsPins[i], HIGH);
  }
  digitalWrite(kCsPins[id], LOW);
}

void DeselectChips() {
  for (size_t i = 0; i < kNumAdcIc; i++) {
    digitalWrite(kCsPins[i], HIGH);
  }
}

// Fetch a ADC result of a specified channel from a MCP3208.
int16_t ReadMcp3208Adc(uint8_t chipId, uint8_t channel) {
  SelectChip(chipId);
  // MCP3208 receives only 5 bits for start.
  // Since the SPI library only supports bytewise tramsmission,
  // we send dummy (high-level) bits before the start bit.
  // Send data :
  // 3 dummy bits (000)
  // start bit (1)
  // select single-end (1)
  // 3 address bits: d2, d1, d0
  SPI.transfer(0x18 | channel);
  uint16_t b0 = SPI.transfer(0x00);
  uint16_t b1 = SPI.transfer(0x00);
  DeselectChips();
  // The first output bit is high-Z (sampling period).
  // The second bit is always 0.
  // Then the ADC value follows in MSB first format.
  // Therefore the first received byte contains 6 bits from MSB,
  // and the second byte contains the remainder.
  return ((b0 & 0x3f) << 6) | ((b1 & 0xfc) >> 2);
}

void ReadSwitches(bool* button) {
  for (size_t i = 0; i < 12; i++) {
    button[i] = (digitalRead(kButtonPins[i]) == LOW);
  }
}

void ReadVolumes(uint16_t* data) {
  byte inByte = 0;
  for (uint8_t j = 0; j < kNumAdcIc; j++) {
    for (uint8_t i = 0; i < 8; i++) {
      data[j * 8 + i] = ReadMcp3208Adc(j, i);
    }
  }
}

// Passes through any serial input to the output.
// This mode can be used to configure RN-42 using serial terminal
// connected to Arduino.
void EchoBackMode() {
  while (true) {
    if (Serial.available()) {
      Serial.print((char)Serial.read());
    }
  }
}

void loop() {
  if (Serial.available() && Serial.read() == '!') {
    EchoBackMode();
  }

  SensorData keys;
  ReadVolumes(keys.axes);
  ReadSwitches(keys.button);
  int nOutputs;
  const char* outputs[COLS];
  keyboard.ProcessSensorData(keys, COLS, outputs, &nOutputs);
  for (size_t i = 0; i < nOutputs; i++) {
    Serial.print(outputs[i]);
  }
}


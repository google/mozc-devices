#include <SPI.h>
#include <Wire.h>
#include "flick_keyboard.h"

// Number of A/D converter ICs.
const int kNumAdcIc = 3;                    // MCP3008 x 3 Chips
const int kCsPins[kNumAdcIc] = {8, 9, 10};  // MCP3008 SS Pins in Arduino nano

// Tact Switch(without XY tilt) Setting
const int kStaticButtonPins[8] = {4, 5, 6, 7, A3, A2, A1, A0};

// LED Setting on Arduino nano
const int kLedPin = 13;

// GPIO to I2C IC Setting
const int kMcp23017Addr = 0x20;             // I2C Address

FlickKeyboard keyboard;

void setup() {
  Serial.begin(115200);

  pinMode(kLedPin, OUTPUT);                 // Led
  digitalWrite(kLedPin, LOW);

  for (size_t i = 0; i < kNumAdcIc; i++) {
    pinMode(kCsPins[i], OUTPUT);
    digitalWrite(kCsPins[i], HIGH);
  }
  for (size_t i = 0; i < 8; i++) {
    pinMode(kStaticButtonPins[i], INPUT);
  }
  SPI.begin();                              // Enable SPI
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));

  Wire.begin();                            // Enable I2C
  Mcp23017Init();
}

void loop() {
  if (Serial.available() && Serial.read() == '!') {
    EchoBackMode();
  }

  SensorData keys;
  ReadVolumes(keys.axes);                        // Read flick axes
  for (size_t i = FLICKS; i < COLS; i++) {       // Set center position to tact switch button's axes
    keys.axes[i*2] = (1 << (ADC_BITS-1));
    keys.axes[i*2+1] = (1 << (ADC_BITS-1));
  }
  ReadSwitches(keys.button);                    // Read flick buttons

  int nOutputs;
  const char* outputs[COLS];
  keyboard.ProcessSensorData(keys, COLS, outputs, &nOutputs);
  for (size_t i = 0; i < nOutputs; i++) {
    Serial.print(outputs[i]);
  }
  delay(10);
}

// ==========================================================================

void Mcp23017Init() {
  Wire.beginTransmission(kMcp23017Addr);   // Set input mode on port A
  Wire.write(0x00);
  Wire.write(0xff);
  Wire.endTransmission();
  Wire.beginTransmission(kMcp23017Addr);   // Set input mode on port B
  Wire.write(0x01);
  Wire.write(0xff);
  Wire.endTransmission();
  Wire.beginTransmission(kMcp23017Addr);   // Set enable pull-up on port A
  Wire.write(0x0c);
  Wire.write(0xff);
  Wire.endTransmission();
  Wire.beginTransmission(kMcp23017Addr);   // Set enable pull-up on port B
  Wire.write(0x0d);
  Wire.write(0xff);
  Wire.endTransmission();
}

void ReadSwitches(bool* button) {
  byte Mcp23017PortA, Mcp23017PortB;
  Wire.beginTransmission(kMcp23017Addr);   // Read port A
  Wire.write(0x12);
  Wire.endTransmission();
  Wire.requestFrom(kMcp23017Addr, 1);
  Mcp23017PortA = Wire.read();             // Store port A data to Mcp23017PortA
  Mcp23017PortA = ~Mcp23017PortA;          // Invert port A

  Wire.beginTransmission(kMcp23017Addr);   // Read port B
  Wire.write(0x13);
  Wire.endTransmission();
  Wire.requestFrom(kMcp23017Addr, 1);
  Mcp23017PortB = Wire.read();             // Store port B data to Mcp23017PortA
  Mcp23017PortB = ~Mcp23017PortB;          // Invert port B


  byte TestBit = 0x01;
  for (size_t i = 0; i < 8; i++) {
    button[i] = ((Mcp23017PortA & TestBit) != 0);
    TestBit = TestBit << 1;
  }
  TestBit = 0x01;
  for (size_t i = 0; i < 4; i++) {
    button[i + 8] = ((Mcp23017PortB & TestBit) != 0);
    TestBit = TestBit << 1;
  }
  for (size_t i = 0; i < 8; i++) {
    button[i + 12] = (digitalRead(kStaticButtonPins[i]) == HIGH);
  }
}

// Enable MCP3008 SS pins
void SelectChip(uint8_t id) {
  if (id > kNumAdcIc) {
    return;
  }
  for (size_t i = 0; i < kNumAdcIc; i++) {
    digitalWrite(kCsPins[i], HIGH);
  }
  digitalWrite(kCsPins[id], LOW);
}

// Disable MCP3008 SS pins
void DeselectChips() {
  for (size_t i = 0; i < kNumAdcIc; i++) {
    digitalWrite(kCsPins[i], HIGH);
  }
}

// Fetch a ADC result of a specified channel from a MCP3008.
int16_t ReadMcp3008Adc(uint8_t chipId, uint8_t channel) {
  SelectChip(chipId);
  SPI.transfer(0x01);                             // Send start bit
  byte b0 = SPI.transfer((channel << 4) | 0x80);  // Send channel and read analog high byte
  byte b1 = SPI.transfer(0x00);                   // Read analog low byte
  DeselectChips();
  return ((b0 & 0x03) << 8) | b1;
}

void ReadVolumes(uint16_t* data) {
  byte inByte = 0;
  for (uint8_t j = 0; j < kNumAdcIc; j++) {
    for (uint8_t i = 0; i < 8; i++) {
      data[j * 8 + i] = ReadMcp3008Adc(j, i);
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


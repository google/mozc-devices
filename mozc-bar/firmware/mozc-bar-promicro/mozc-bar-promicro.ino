#include "Keyboard.h"

const auto DATA = 4;  // poci
const auto CLK = 5;   // clk
const auto LOAD = 6;  // pico

const auto MODULES = 17;
const auto KEYBOARD_REPORT_ID = 2;

#define PCB_WITH_1_KEY(k7) 0, 0, 0, 0, k7, 0, 0, 0
#define PCB_WITH_2_KEYS(k6, k7) 0, 0, 0, 0, k7, k6, 0, 0
#define PCB_WITH_3_KEYS(k5, k6, k7) 0, 0, 0, 0, k7, k6, k5, 0
#define PCB_WITH_4_KEYS(k4, k5, k6, k7) 0, 0, 0, 0, k7, k6, k5, k4
#define PCB_WITH_5_KEYS(k3, k4, k5, k6, k7) k3, 0, 0, 0, k7, k6, k5, k4
#define PCB_WITH_6_KEYS(k2, k3, k4, k5, k6, k7) k3, k2, 0, 0, k7, k6, k5, k4
#define PCB_WITH_7_KEYS(k1, k2, k3, k4, k5, k6, k7) \
  k3, k2, k1, 0, k7, k6, k5, k4
#define PCB_WITH_8_KEYS(k0, k1, k2, k3, k4, k5, k6, k7) \
  k3, k2, k1, k0, k7, k6, k5, k4

#define PCB_TYPE_A PCB_WITH_8_KEYS
#define PCB_TYPE_B PCB_WITH_4_KEYS
#define PCB_TYPE_C PCB_WITH_7_KEYS
#define PCB_TYPE_D PCB_WITH_1_KEY
#define PCB_TYPE_E PCB_WITH_7_KEYS
#define PCB_TYPE_F PCB_WITH_4_KEYS
#define PCB_TYPE_G PCB_WITH_6_KEYS

// 0 means no key.
// PCB-order: right to left.
// Key-order in PCB:  right to left.
const uint8_t keymap[MODULES * 8] PROGMEM = {
    PCB_TYPE_G(  // Board 16
        0x58,    // Enter
        0x57,    // +
        0x63,    // .
        0x62,    // 0
        0x61,    // 9
        0x60     // 8
        ),
    PCB_TYPE_A(  // Board 15
        0x5F,    // 7
        0x5E,    // 6
        0x5D,    // 5
        0x5C,    // 4
        0x5B,    // 3
        0x5A,    // 2
        0x59,    // 1
        0x56     // -
        ),
    PCB_TYPE_A(  // Board 14
        0x55,    // *
        0x54,    // /
        0x53,    // Num Lock
        0x4F,    // →
        0x52,    // ↑
        0x4F,    // ↓
        0x4F,    // ←
        0x4E     // PgDn
        ),
    PCB_TYPE_A(  // Board 13
        0x4D,    // End
        0x4C,    // Delete
        0x4B,    // PgUp
        0x4A,    // Home
        0x49,    // Insert
        0x48,    // Pause
        0x47,    // Scroll Lock
        0x46     // PrtSc
        ),
    PCB_TYPE_F(  // Board 12
        0x2A,    // Backspace
        0x31,    // '\'
        0x28,    // Enter
        0xE5     // Right Shift
        ),
    PCB_TYPE_E(  // Board 11
        0xE4,    // Right Ctrl
        0xE6,    // Right Alt
        0x38,    // ?
        0x37,    // >
        0x36,    // <
        0x10,    // M
        0x11     // N
        ),
    PCB_TYPE_B(  // Board 10
        0x34,    // "
        0x33,    // ;
        0x0F,    // L
        0x0E     // K
        ),
    PCB_TYPE_A(  // Board 9
        0x0D,    // J
        0x0B,    // H
        0x30,    // ]
        0x2F,    // [
        0x13,    // P
        0x12,    // O
        0x0C,    // I
        0x18     // U
        ),
    PCB_TYPE_A(  // Board 8
        0x1C,    // Y
        0x2E,    // =
        0x2D,    // -
        0x27,    // 0
        0x26,    // 9
        0x25,    // 8
        0x24,    // 7
        0x23     // 6
        ),
    PCB_TYPE_D(  // Board 7
        0x2C     // Space
        ),
    PCB_TYPE_B(  // Board 6
        0x05,    // B
        0x19,    // V
        0x06,    // C
        0x1B     // X
        ),
    PCB_TYPE_A(  // Board 5
        0x1D,    // Z
        0x0A,    // G
        0x09,    // F
        0x07,    // D
        0x16,    // S
        0x04,    // A
        0x17,    // T
        0x15     // R
        ),
    PCB_TYPE_A(  // Board 4
        0x08,    // E
        0x1A,    // W
        0x14,    // Q
        0x22,    // 5
        0x21,    // 4
        0x20,    // 3
        0x1F,    // 2
        0x1E     // 1
        ),
    PCB_TYPE_C(  // Board 3
        0xE2,    // Left Alt
        0xE0,    // Left Ctrl
        0xE1,    // Left shift
        0x39,    // CapsLock
        0x2B,    // Tab
        0x35,    // ~
        0x45     // F12
        ),
    PCB_TYPE_B(  // Board 2
        0x44,    // F11
        0x43,    // F10
        0x42,    // F9
        0x41     // F8
        ),
    PCB_TYPE_A(  // Board 1
        0x40,    // F7
        0x3F,    // F6
        0x3E,    // F5
        0x3D,    // F4
        0x3C,    // F3
        0x3B,    // F2
        0x3A,    // F1
        0x29     // Esc
        ),
};


void setup() {
  Keyboard.begin();
  pinMode(DATA, INPUT_PULLUP);
  pinMode(CLK, OUTPUT);
  digitalWrite(CLK, LOW);
  pinMode(LOAD, OUTPUT);
  digitalWrite(LOAD, HIGH);
}

void read_keys(uint8_t* buf) {
  digitalWrite(LOAD, LOW);
  delay(10);
  digitalWrite(LOAD, HIGH);
  delay(10);

  for (int i = 0; i < MODULES; i++) {
    uint8_t data = 0;
    for (int j = 0; j < 8; j++) {
      bool state = digitalRead(DATA) == LOW;
      data = data | (state ? 1 << j : 0);
      digitalWrite(CLK, HIGH);
      digitalWrite(CLK, LOW);
    }
    buf[i] = data;
  }
}

void send_report(uint8_t* buf) {
  KeyReport key_report = {0};
  int pushed_keys = 0;
  for (int i = 0; i < MODULES * 8; i++) {
    int module_id = i / 8;
    int keymask = 1 << (i % 8);
    if ((buf[module_id] & keymask) != 0) {
      uint8_t keycode = pgm_read_byte(keymap + i);
      if (0xE0 <= keycode && keycode <= 0xE7) {
        key_report.modifiers |= (1 << (keycode - 0xE0));
      } else {
        key_report.keys[pushed_keys] = keycode;
        pushed_keys++;
        if (pushed_keys == 6) break;
      }
    }
  }
  HID().SendReport(KEYBOARD_REPORT_ID, &key_report, sizeof(KeyReport));
}

uint8_t keybuf[2][MODULES];
uint8_t current_buffer = 0;
void loop() {
  read_keys(keybuf[current_buffer]);
  if (memcmp(keybuf[0], keybuf[1], MODULES) != 0) {
    send_report(keybuf[current_buffer]);
    current_buffer = 1 - current_buffer;
  }
}

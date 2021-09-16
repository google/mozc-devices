
// Uncomment next line if your PC thinks this is US keyboard.
#define JP_KEYBOARD

#include "Keyboard.h"

// COLS = PD0, PD1, PD2, PD3, PD4, PD5
// ROWS = PB0, PB1, PB2, PB3, PB4

#define COL B10000000
#define ROW B00000000

typedef enum {
  C0 = COL + 0,
  C1 = COL + 1,
  C2 = COL + 2,
  C3 = COL + 3,
  C4 = COL + 4,
  C5 = COL + 5,

  R0 = ROW + 0,
  R1 = ROW + 1,
  R2 = ROW + 2,
  R3 = ROW + 3,
  R4 = ROW + 4,
} Pin;

#define ROWS 5
#define COLS 12

Pin keys[5][12][2] = {
    {
        {C0, R4},
        {C1, R0},
        {C2, R1},
        {C3, R2},
        {C4, R3},
        {C5, R4},
        {R0, C0},
        {R1, C1},
        {R2, C2},
        {R3, C3},
        {R4, C4},
        {R0, C5},
    },
    {
        {C0, R3},
        {C1, R4},
        {C2, R0},
        {C3, R1},
        {C4, R2},
        {C5, R3},
        {R4, C0},
        {R0, C1},
        {R1, C2},
        {R2, C3},
        {R3, C4},
        {R4, C5},
    },
    {
        {C0, R2},
        {C1, R3},
        {C2, R4},
        {C3, R0},
        {C4, R1},
        {C5, R2},
        {R3, C0},
        {R4, C1},
        {R0, C2},
        {R1, C3},
        {R2, C4},
        {R3, C5},
    },
    {
        {C0, R1},
        {C1, R2},
        {C2, R3},
        {C3, R4},
        {C4, R0},
        {C5, R1},
        {R2, C0},
        {R3, C1},
        {R4, C2},
        {R0, C3},
        {R1, C4},
        {R2, C5},
    },
    {
        {C0, R0},
        {C1, R1},
        {C2, R2},
        {C3, R3},
        {C4, R4},
        {C5, R0},
        {R1, C0},
        {R2, C1},
        {R3, C2},
        {R4, C3},
        {R0, C4},
        {R1, C5},
    },
};

uint16_t chars[5][12] = {
    {
        0x9BCF,
        0x9BF5,
        0x9B8E,
        0x9BC7,
        0x9B91,
        0x9B66,
        0x9BD4,
        0x9BC6,
        0x9C2F,
        0x9B87,
        0x9BCF,
        0x9C53,
    },
    {
        0x9C3B,
        0x9C4F,
        0x9C5B,
        0x9C15,
        0x9C27,
        0x9C0D,
        0x9C39,
        0x9C5F,
        0x9B73,
        0x9C08,
        0x9B8D,
        0x9C5A,
    },
    {
        0x9BE8,
        0x9BC9,
        0x9BD2,
        0x9B97,
        0x9BB4,
        0x9BAD,
        0x9BEF,
        0x9BD6,
        0x9BAB,
        0x9C75,
        0x9C06,
        0x9BE2,
    },
    {
        0x9C6A,
        0x9BF1,
        0x9B8A,
        0x9BF3,
        0x9C78,
        0x9BD0,
        0x9BAC,
        0x9BDB,
        0x9C16,
        0x9C31,
        0x9BB9,
        0x9B5B,
    },
    {
        0x9C48,
        0x9C58,
        0x9C45,
        0x9C0C,
        0x9BD4,
        0x9BF0,
        0x9C0A,
        0x9BB8,
        0x9BCA,
        0x9C23,
        0x9C30,
        0x9B6C,
    },
};

void setup() {
  Keyboard.begin();
  Serial.begin(9600);
  DDRD = 0;
  PORTD = B00111111;
  DDRB = 0;
  PORTB = B00011111;
  delay(100);
}

void selectRow(Pin p) {
  bool col = !!(COL & p);
  byte mask = 1 << (p & B01111111);
  if (col) {
    DDRD = mask;
    PORTD = ~mask;
  } else {
    DDRB = mask;
    PORTB = ~mask;
  }
}

bool readCol(Pin p) {
  bool col = !!(COL & p);
  byte mask = 1 << (p & B01111111);
  return ((col ? PIND : PINB) & mask) == 0;
}

#define KEYBOARD_REPORT_ID 2

void sendKeyPush(uint8_t code, bool shift) {
  KeyReport keys;
  keys.keys[0] = 0;
  keys.keys[1] = 0;
  keys.keys[2] = 0;
  keys.keys[3] = 0;
  keys.keys[4] = 0;
  keys.keys[5] = 0;
  keys.modifiers = 0x00;
  if (shift) {
    keys.modifiers = 0x02;
    HID().SendReport(KEYBOARD_REPORT_ID, &keys, sizeof(KeyReport));
  }
  keys.keys[0] = code;
  HID().SendReport(KEYBOARD_REPORT_ID, &keys, sizeof(KeyReport));
  keys.keys[0] = 0;
  HID().SendReport(KEYBOARD_REPORT_ID, &keys, sizeof(KeyReport));
  if (shift) {
    keys.modifiers = 0;
    HID().SendReport(KEYBOARD_REPORT_ID, &keys, sizeof(KeyReport));
  }
}

#define KEY_0 0x27
#define KEY_1 0x1e
#define KEY_2 0x1f
#define KEY_3 0x20
#define KEY_4 0x21
#define KEY_5 0x22
#define KEY_6 0x23
#define KEY_7 0x24
#define KEY_8 0x25
#define KEY_9 0x26

#define KEY_A 0x04
#define KEY_B 0x05
#define KEY_C 0x06
#define KEY_D 0x07
#define KEY_E 0x08
#define KEY_F 0x09
#define KEY_U 0x18
#define KEY_EQUAL 0x2e
#define KEY_SEMICOLON 0x33
#define KEY_SPC 0x2c
#define KEY_ENT 0x28

void sendHex(int16_t in) {
  static const uint8_t codes[] = {
      KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7,
      KEY_8, KEY_9, KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F,
  };
  static const bool shifts[] = {
      false, false, false, false, false, false, false, false,
      false, false, true,  true,  true,  true,  true,  true,
  };
  for (int i = 0; i < 4; i++) {
    byte f = (in >> ((3 - i) * 4)) & 0xf;
    sendKeyPush(codes[f], shifts[f]);
  }
}

int c = 0;

void loop() {
  delay(10);
  Serial.println("--------");
  for (int r = 0; r < ROWS; r++) {
    for (int c = 0; c < COLS; c++) {
      Pin* key = keys[r][c];
      selectRow(key[0]);
      delayMicroseconds(10);
      bool pushed = readCol(key[1]);
      Serial.print(pushed ? "1" : "0");
      if (pushed) {
        sendKeyPush(KEY_U, true);
#ifdef JP_KEYBOARD
        sendKeyPush(KEY_SEMICOLON, true);
#else
        sendKeyPush(KEY_EQUAL, true);
#endif
        sendHex(chars[r][c]);
        sendKeyPush(KEY_SPC, false);
        sendKeyPush(KEY_SPC, false);
        sendKeyPush(KEY_ENT, false);
        delay(100);
      }
      DDRD = 0;
      PORTD = B00111111;
      DDRB = 0;
      PORTB = B00011111;
    }
    Serial.println();
  }
}

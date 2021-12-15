// Uncomment next line if you use ProMicro
// #define PRO_MICRO

// Uncomment next line if your PC thinks this is US keyboard.
// #define JP_KEYBOARD

#include "Keyboard.h"

#ifdef PRO_MICRO

// COLS = 9,8,7,6,5,4
// ROWS = 18,15,14,16,10

typedef enum {
  C0 = 9,
  C1 = 8,
  C2 = 7,
  C3 = 6,
  C4 = 5,
  C5 = 4,
  R0 = 18,
  R1 = 15,
  R2 = 14,
  R3 = 16,
  R4 = 10,
} Pin;

#define PINS 11
Pin pins[] = {C0, C1, C2, C3, C4, C5, R0, R1, R2, R3, R4};

#else

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

#endif

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
        0x0040,  // @
        0x002b,  // +
        0x9c19,  // 鰙
        0x9c73,  // 鱳
        0x9c25,  // 鰥
        0x9baa,  // 鮪
        0x9c30,  // 鰰
        0x9c60,  // 鱠
        0x9bdb,  // 鯛
        0x9bd6,  // 鯖
        0x9c39,  // 鰹
        0x9bf5,  // 鯵
    },
    {
        0x0020,  //
        0x002d,  // -
        0x0021,  // !
        0x9bda,  // 鯚
        0x002c,  // ,
        0x9bab,  // 鮫
        0x9c2d,  // 鰭
        0x9c0a,  // 鰊
        0x9c58,  // 鱘
        0x9bf1,  // 鯱
        0x9c5a,  // 鱚
        0x9c2f,  // 鰯
    },
    {
        0x005f,  // _
        0x002a,  // *
        0x9b5a,  // 魚
        0x9bcd,  // 鯍
        0x9b77,  // 魷
        0x9be5,  // 鯥
        0x9c24,  // 鰤
        0x9c56,  // 鱖
        0x9c41,  // 鱁
        0x9c78,  // 鱸
        0x9be8,  // 鯨
        0x9c3b,  // 鰻
    },
    {
        0x003d,  // =
        0x002f,  // /
        0x003f,  // ?
        0x9c7a,  // 鱺
        0x002e,  // .
        0x9bb4,  // 鮴
        0x9b83,  // 鮃
        0x9bf0,  // 鯰
        0x9bf3,  // 鯳
        0x9bac,  // 鮬
        0x9b5d,  // 魝
        0x9c4f,  // 鱏
    },
    {
        0x9ba8,  // 鮨
        0x8336,  // 茶
        0x9c77,  // 鱷
        0x9b6f,  // 魯
        0x9c29,  // 鰩
        0x9b79,  // 魹
        0x9bd4,  // 鯔
        0x9b76,  // 魶
        0x9c0c,  // 鰌
        0x9bfc,  // 鯼
        0x9bc9,  // 鯉
        0x9c27,  // 鰧
    },
};

void selectRow(Pin p) {
#ifdef PRO_MICRO

  pinMode(p, OUTPUT);
  digitalWrite(p, LOW);

#else

  bool col = !!(COL & p);
  byte mask = 1 << (p & B01111111);
  if (col) {
    DDRD = mask;
    PORTD = ~mask;
  } else {
    DDRB = mask;
    PORTB = ~mask;
  }

#endif
}

void unselectRows() {
#ifdef PRO_MICRO

  for (byte i = 0; i < PINS; i++) {
    pinMode(pins[i], INPUT_PULLUP);
  }

#else

  DDRD = 0;
  PORTD = B00111111;
  DDRB = 0;
  PORTB = B00011111;

#endif
}

bool readCol(Pin p) {
#ifdef PRO_MICRO

  return digitalRead(p) == LOW;

#else

  bool col = !!(COL & p);
  byte mask = 1 << (p & B01111111);
  return ((col ? PIND : PINB) & mask) == 0;

#endif
}

void setup() {
  Keyboard.begin();
  Serial.begin(9600);

  unselectRows();

  delay(100);
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
      selectRow(key[1]);
      delayMicroseconds(10);
      bool pushed = readCol(key[0]);
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
      unselectRows();
    }
    Serial.println();
  }
}

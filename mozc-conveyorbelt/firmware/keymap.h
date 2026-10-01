// Copyright 2026 Google Inc.
// Use of this source code is governed by an Apache License that can be found
// in the LICENSE file.

#ifndef __keymap_h__
#define __keymap_h__

#include <stdbool.h>
#include <stdint.h>

// Layout map (15 rows x 8 columns = 120 keys, MSB to LSB per row):
//          Bit 7      Bit 6      Bit 5      Bit 4      Bit 3      Bit 2      Bit 1      Bit 0
// Byte  0: None       None       None       None       None       CapsLock   PageUp     PageDown
// Byte  1: Left       Down       Up         Right      1          q          a          z
// Byte  2: 2          w          s          x          3          e          d          c
// Byte  3: 4          r          f          v          5          t          g          b
// Byte  4: 6          y          h          n          7          u          j          m
// Byte  5: 8          i          k          ,          9          o          l          .
// Byte  6: 0          p          ;          /          -          [          '          Space
// Byte  7: =          ]          GUI(GOOG)  Backspace  `          \          Control    Enter
// Byte  8: Escape     Shift      Alt        Tab        !          Q          A          Z
// Byte  9: @          W          S          X          #          E          D          C
// Byte 10: $          R          F          V          %          T          G          B
// Byte 11: ^          Y          H          N          &          U          J          M
// Byte 12: *          I          K          <          (          O          L          >
// Byte 13: )          P          :          ?          _          {          "          Fn
// Byte 14: +          }          Insert     Delete     ~          |          Home       End

struct keymap_entry {
  uint8_t keycode;
  bool shift;
};

// Special keys (internal control / error):
// - KEY_NONE           (0x00): No key mapped.
// - KEY_ERROR_ROLLOVER (0x01): Exceeded 6KRO simultaneous key limit.
// - KEY_FN             (0xFF): Fn key; toggles numeric keys to F1-F10 layer.
#define KEY_NONE            0x00
#define KEY_ERROR_ROLLOVER  0x01
#define KEY_FN              0xff

// HID Modifiers (Usage IDs 0xE0-0xE7):
// NOTE: Unlike standard keys (0x04-0x65) which are sent in HID report bytes 2..7,
// these modifier keys must be converted into bit flags in report byte 0:
//   KEY_LCTRL  (0xE0) -> (1 << 0)
//   KEY_LSHIFT (0xE1) -> (1 << 1)
//   KEY_LALT   (0xE2) -> (1 << 2)
//   KEY_LGUI   (0xE3) -> (1 << 3) (GOOG / GUI key)
#define KEY_LCTRL       0xe0
#define KEY_LSHIFT      0xe1
#define KEY_LALT        0xe2
#define KEY_LGUI        0xe3  // GOOG

#define MOD_LCTRL       (1 << 0)
#define MOD_LSHIFT      (1 << 1)
#define MOD_LALT        (1 << 2)
#define MOD_LGUI        (1 << 3)

// HID Usage Tables - Keyboard / Keypad (Page 0x07)
#define KEY_A           0x04
#define KEY_B           0x05
#define KEY_C           0x06
#define KEY_D           0x07
#define KEY_E           0x08
#define KEY_F           0x09
#define KEY_G           0x0a
#define KEY_H           0x0b
#define KEY_I           0x0c
#define KEY_J           0x0d
#define KEY_K           0x0e
#define KEY_L           0x0f
#define KEY_M           0x10
#define KEY_N           0x11
#define KEY_O           0x12
#define KEY_P           0x13
#define KEY_Q           0x14
#define KEY_R           0x15
#define KEY_S           0x16
#define KEY_T           0x17
#define KEY_U           0x18
#define KEY_V           0x19
#define KEY_W           0x1a
#define KEY_X           0x1b
#define KEY_Y           0x1c
#define KEY_Z           0x1d

#define KEY_1           0x1e
#define KEY_2           0x1f
#define KEY_3           0x20
#define KEY_4           0x21
#define KEY_5           0x22
#define KEY_6           0x23
#define KEY_7           0x24
#define KEY_8           0x25
#define KEY_9           0x26
#define KEY_0           0x27

#define KEY_ENTER       0x28
#define KEY_ESC         0x29
#define KEY_BS          0x2a
#define KEY_TAB         0x2b
#define KEY_SPACE       0x2c
#define KEY_MINUS       0x2d  // JIS: - / =
#define KEY_CARET       0x2e  // JIS: ^ / ~
#define KEY_AT          0x2f  // JIS: @ / `
#define KEY_LBRACKET    0x30  // JIS: [ / {
#define KEY_RBRACKET    0x31  // JIS: ] / }
#define KEY_SEMICOLON   0x33  // JIS: ; / +
#define KEY_COLON       0x34  // JIS: : / *
#define KEY_COMMA       0x36  // JIS: , / <
#define KEY_DOT         0x37  // JIS: . / >
#define KEY_SLASH       0x38  // JIS: / / ?
#define KEY_CAPSLOCK    0x39

#define KEY_F1          0x3a
#define KEY_F2          0x3b
#define KEY_F3          0x3c
#define KEY_F4          0x3d
#define KEY_F5          0x3e
#define KEY_F6          0x3f
#define KEY_F7          0x40
#define KEY_F8          0x41
#define KEY_F9          0x42
#define KEY_F10         0x43

#define KEY_INSERT      0x49
#define KEY_HOME        0x4a
#define KEY_PAGEUP      0x4b
#define KEY_DELETE      0x4c
#define KEY_END         0x4d
#define KEY_PAGEDOWN    0x4e
#define KEY_RIGHT       0x4f
#define KEY_LEFT        0x50
#define KEY_DOWN        0x51
#define KEY_UP          0x52

#define KEY_RO          0x87  // JIS: \ / _ (ろ)
#define KEY_YEN         0x89  // JIS: ￥ / | (Intl 3)

#define KEYMAP_SIZE 120

// 120 key mappings matching shift register read order (Byte 0..14, MSB..LSB).
// JIS (Japanese) layout mapping.
static const struct keymap_entry keymap[KEYMAP_SIZE] = {
    // Byte 0: None None None None None CapsLock PageUp PageDown
    {KEY_NONE, false},       // bit 7: None
    {KEY_NONE, false},       // bit 6: None
    {KEY_NONE, false},       // bit 5: None
    {KEY_NONE, false},       // bit 4: None
    {KEY_NONE, false},       // bit 3: None
    {KEY_CAPSLOCK, false},   // bit 2: CapsLock
    {KEY_PAGEUP, false},     // bit 1: PageUp
    {KEY_PAGEDOWN, false},   // bit 0: PageDown

    // Byte 1: Left Down Up Right 1 q a z
    {KEY_LEFT, false},       // bit 7: Left
    {KEY_DOWN, false},       // bit 6: Down
    {KEY_UP, false},         // bit 5: Up
    {KEY_RIGHT, false},      // bit 4: Right
    {KEY_1, false},          // bit 3: 1
    {KEY_Q, false},          // bit 2: q
    {KEY_A, false},          // bit 1: a
    {KEY_Z, false},          // bit 0: z

    // Byte 2: 2 w s x 3 e d c
    {KEY_2, false},          // bit 7: 2
    {KEY_W, false},          // bit 6: w
    {KEY_S, false},          // bit 5: s
    {KEY_X, false},          // bit 4: x
    {KEY_3, false},          // bit 3: 3
    {KEY_E, false},          // bit 2: e
    {KEY_D, false},          // bit 1: d
    {KEY_C, false},          // bit 0: c

    // Byte 3: 4 r f v 5 t g b
    {KEY_4, false},          // bit 7: 4
    {KEY_R, false},          // bit 6: r
    {KEY_F, false},          // bit 5: f
    {KEY_V, false},          // bit 4: v
    {KEY_5, false},          // bit 3: 5
    {KEY_T, false},          // bit 2: t
    {KEY_G, false},          // bit 1: g
    {KEY_B, false},          // bit 0: b

    // Byte 4: 6 y h n 7 u j m
    {KEY_6, false},          // bit 7: 6
    {KEY_Y, false},          // bit 6: y
    {KEY_H, false},          // bit 5: h
    {KEY_N, false},          // bit 4: n
    {KEY_7, false},          // bit 3: 7
    {KEY_U, false},          // bit 2: u
    {KEY_J, false},          // bit 1: j
    {KEY_M, false},          // bit 0: m

    // Byte 5: 8 i k , 9 o l .
    {KEY_8, false},          // bit 7: 8
    {KEY_I, false},          // bit 6: i
    {KEY_K, false},          // bit 5: k
    {KEY_COMMA, false},      // bit 4: ,
    {KEY_9, false},          // bit 3: 9
    {KEY_O, false},          // bit 2: o
    {KEY_L, false},          // bit 1: l
    {KEY_DOT, false},        // bit 0: .

    // Byte 6: 0 p ; / - [ ' Space
    {KEY_0, false},          // bit 7: 0
    {KEY_P, false},          // bit 6: p
    {KEY_SEMICOLON, false},  // bit 5: ;
    {KEY_SLASH, false},      // bit 4: /
    {KEY_MINUS, false},      // bit 3: -
    {KEY_LBRACKET, false},   // bit 2: [
    {KEY_7, true},           // bit 1: ' (JIS: Shift + 7)
    {KEY_SPACE, false},      // bit 0: Space

    // Byte 7: = ] GUI(GOOG) Backspace ` \ Control Enter
    {KEY_MINUS, true},       // bit 7: = (JIS: Shift + -)
    {KEY_RBRACKET, false},   // bit 6: ]
    {KEY_LGUI, false},       // bit 5: GUI (GOOG)
    {KEY_BS, false},         // bit 4: Backspace
    {KEY_AT, true},          // bit 3: ` (JIS: Shift + @)
    {KEY_YEN, false},        // bit 2: \ (JIS: ￥)
    {KEY_LCTRL, false},      // bit 1: Control
    {KEY_ENTER, false},      // bit 0: Enter

    // Byte 8: Escape Shift Alt Tab ! Q A Z
    {KEY_ESC, false},        // bit 7: Escape
    {KEY_LSHIFT, false},     // bit 6: Shift
    {KEY_LALT, false},       // bit 5: Alt
    {KEY_TAB, false},        // bit 4: Tab
    {KEY_1, true},           // bit 3: ! (Shift + 1)
    {KEY_Q, true},           // bit 2: Q (Shift + q)
    {KEY_A, true},           // bit 1: A (Shift + a)
    {KEY_Z, true},           // bit 0: Z (Shift + z)

    // Byte 9: @ W S X # E D C
    {KEY_AT, false},         // bit 7: @ (JIS: @)
    {KEY_W, true},           // bit 6: W (Shift + w)
    {KEY_S, true},           // bit 5: S (Shift + s)
    {KEY_X, true},           // bit 4: X (Shift + x)
    {KEY_3, true},           // bit 3: # (Shift + 3)
    {KEY_E, true},           // bit 2: E (Shift + e)
    {KEY_D, true},           // bit 1: D (Shift + d)
    {KEY_C, true},           // bit 0: C (Shift + c)

    // Byte 10: $ R F V % T G B
    {KEY_4, true},           // bit 7: $ (Shift + 4)
    {KEY_R, true},           // bit 6: R (Shift + r)
    {KEY_F, true},           // bit 5: F (Shift + f)
    {KEY_V, true},           // bit 4: V (Shift + v)
    {KEY_5, true},           // bit 3: % (Shift + 5)
    {KEY_T, true},           // bit 2: T (Shift + t)
    {KEY_G, true},           // bit 1: G (Shift + g)
    {KEY_B, true},           // bit 0: B (Shift + b)

    // Byte 11: ^ Y H N & U J M
    {KEY_CARET, false},      // bit 7: ^ (JIS: ^)
    {KEY_Y, true},           // bit 6: Y (Shift + y)
    {KEY_H, true},           // bit 5: H (Shift + h)
    {KEY_N, true},           // bit 4: N (Shift + n)
    {KEY_6, true},           // bit 3: & (JIS: Shift + 6)
    {KEY_U, true},           // bit 2: U (Shift + u)
    {KEY_J, true},           // bit 1: J (Shift + j)
    {KEY_M, true},           // bit 0: M (Shift + m)

    // Byte 12: * I K < ( O L >
    {KEY_COLON, true},       // bit 7: * (JIS: Shift + :)
    {KEY_I, true},           // bit 6: I (Shift + i)
    {KEY_K, true},           // bit 5: K (Shift + k)
    {KEY_COMMA, true},       // bit 4: < (Shift + ,)
    {KEY_8, true},           // bit 3: ( (JIS: Shift + 8)
    {KEY_O, true},           // bit 2: O (Shift + o)
    {KEY_L, true},           // bit 1: L (Shift + l)
    {KEY_DOT, true},         // bit 0: > (Shift + .)

    // Byte 13: ) P : ? _ { " Fn
    {KEY_9, true},           // bit 7: ) (JIS: Shift + 9)
    {KEY_P, true},           // bit 6: P (Shift + p)
    {KEY_COLON, false},      // bit 5: : (JIS: :)
    {KEY_SLASH, true},       // bit 4: ? (Shift + /)
    {KEY_RO, true},          // bit 3: _ (JIS: Shift + ろ)
    {KEY_LBRACKET, true},    // bit 2: { (JIS: Shift + [)
    {KEY_2, true},           // bit 1: " (JIS: Shift + 2)
    {KEY_FN, false},         // bit 0: Fn

    // Byte 14: + } Insert Delete ~ | Home End
    {KEY_SEMICOLON, true},   // bit 7: + (JIS: Shift + ;)
    {KEY_RBRACKET, true},    // bit 6: } (JIS: Shift + ])
    {KEY_INSERT, false},     // bit 5: Insert
    {KEY_DELETE, false},     // bit 4: Delete
    {KEY_CARET, true},       // bit 3: ~ (JIS: Shift + ^)
    {KEY_YEN, true},         // bit 2: | (JIS: Shift + ￥)
    {KEY_HOME, false},       // bit 1: Home
    {KEY_END, false},        // bit 0: End
};

#endif  // __keymap_h__

// Copyright 2024 Google Inc.
// Use of this source code is governed by an Apache License that can be found in
// the LICENSE file.

#include "hid.h"

#include <stdbool.h>

#include "i2c.h"
#include "usbd_customhid.h"

extern USBD_HandleTypeDef hUsbDeviceFS;

#define REPORT_SIZE 17
#define KEYBOARD_REPORT_ID 1
#define KEYBOARD_REPORT_MODIFIER_OFFSET 1
#define KEYBOARD_REPORT_OFFSET 3
#define UNICODE_REPORT_ID 2
#define UNICODE_REPORT_OFFSET 1
#define KEY_LINES 26
#define KEY_COLUMNS 8

static bool active = false;
static uint8_t prev_keys[KEY_LINES];
static uint8_t prev_key_message[REPORT_SIZE];
static uint8_t key_message[REPORT_SIZE];
static uint8_t key_index = KEYBOARD_REPORT_OFFSET;
static uint8_t unicode_message[REPORT_SIZE];
static uint8_t unicode_index = UNICODE_REPORT_OFFSET;
static uint8_t usage_id[26][8] = {
    {0x1f, 0x1a, 0x16, 0x1d, 0x00, 0x00, 0x00, 0x00},
    {0x20, 0x08, 0x07, 0x1b, 0x00, 0x00, 0x00, 0x00},
    {0x21, 0x15, 0x09, 0x06, 0x00, 0x00, 0x00, 0x00},
    {0x22, 0x17, 0x0a, 0x19, 0x00, 0x00, 0x00, 0x00},
    {0x23, 0x1c, 0x0b, 0x05, 0x00, 0x00, 0x00, 0x00},
    {0x24, 0x18, 0x0d, 0x11, 0x00, 0x00, 0x00, 0x00},
    {0x25, 0x0c, 0x0e, 0x10, 0x00, 0x00, 0x00, 0x00},
    {0x26, 0x12, 0x0f, 0x36, 0x00, 0x00, 0x00, 0x00},
    {0x27, 0x13, 0x33, 0x37, 0x00, 0x00, 0x00, 0x00},
    {0x2d, 0x2f, 0x34, 0x38, 0x00, 0x00, 0x00, 0x00},
    {0x2e, 0x30, 0x32, 0x87, 0x00, 0x00, 0x00, 0x00},
    {0x89, 0x2a, 0x28, 0xe6, 0x00, 0x00, 0x00, 0x00},
    {0x3a, 0x2c, 0xe4, 0xe5, 0x00, 0x00, 0x00, 0x00},
    {0x3b, 0x46, 0x49, 0x4c, 0x00, 0x00, 0x00, 0x00},
    {0x3c, 0x47, 0x4a, 0x4d, 0x00, 0x00, 0x00, 0x00},
    {0x3d, 0x48, 0x4b, 0x4e, 0x00, 0x00, 0x00, 0x00},
    {0x3e, 0x53, 0x50, 0xe3, 0x00, 0x00, 0x00, 0x00},
    {0x3f, 0x52, 0x51, 0x54, 0x00, 0x00, 0x00, 0x00},
    {0x40, 0x55, 0x4f, 0x62, 0x00, 0x00, 0x00, 0x00},
    {0x41, 0x5f, 0x5c, 0x59, 0x00, 0x00, 0x00, 0x00},
    {0x42, 0x60, 0x5d, 0x5a, 0x00, 0x00, 0x00, 0x00},
    {0x43, 0x61, 0x5e, 0x5b, 0x00, 0x00, 0x00, 0x00},
    {0x44, 0x56, 0x57, 0x58, 0x00, 0x00, 0x00, 0x00},
    {0x45, 0x8b, 0x8a, 0x4c, 0x00, 0x00, 0x00, 0x00},
    {0x29, 0x2b, 0xe0, 0xe1, 0x39, 0x88, 0x28, 0x2a},
    {0x1e, 0x14, 0x04, 0xe2, 0x00, 0x00, 0x00, 0x2c},
};

static uint16_t unicode[26][8] = {
    {0xffff, 0xffff, 0xffff, 0xffff, 0x3075, 0x3066, 0x3068, 0x3064},
    {0xffff, 0xffff, 0xffff, 0xffff, 0x3042, 0x3044, 0x3057, 0x3055},
    {0xffff, 0xffff, 0xffff, 0xffff, 0x3046, 0x3059, 0x306f, 0x305d},
    {0xffff, 0xffff, 0xffff, 0xffff, 0x3048, 0x304b, 0x304d, 0x3072},
    {0xffff, 0xffff, 0xffff, 0xffff, 0x304a, 0x3093, 0x304f, 0x3053},
    {0xffff, 0xffff, 0xffff, 0xffff, 0x3084, 0x306a, 0x307e, 0x307f},
    {0xffff, 0xffff, 0xffff, 0xffff, 0x3086, 0x306b, 0x306e, 0x3082},
    {0xffff, 0xffff, 0xffff, 0xffff, 0x3088, 0x3089, 0x308a, 0x306d},
    {0xffff, 0xffff, 0xffff, 0xffff, 0x308f, 0x305b, 0x308c, 0x308b},
    {0xffff, 0xffff, 0xffff, 0xffff, 0x307b, 0x307b, 0x3051, 0x3081},
    {0xffff, 0xffff, 0xffff, 0xffff, 0x3078, 0x309c, 0x3080, 0x308d},
    {0xffff, 0xffff, 0xffff, 0xffff, 0x30FC, 0x0000, 0x0001, 0x0002},
    {0xffff, 0xffff, 0xffff, 0xffff, 0x0003, 0x0004, 0x0005, 0x0006},
    {0xffff, 0xffff, 0xffff, 0xffff, 0x0007, 0x0008, 0x0009, 0x000a},
    {0xffff, 0xffff, 0xffff, 0xffff, 0x000b, 0x000c, 0x000d, 0x000e},
    {0xffff, 0xffff, 0xffff, 0xffff, 0x000f, 0x0010, 0x0011, 0x0012},
    {0xffff, 0xffff, 0xffff, 0xffff, 0x0013, 0x0014, 0x0015, 0x0016},
    {0xffff, 0xffff, 0xffff, 0xffff, 0x0017, 0x0018, 0x0019, 0x001a},
    {0xffff, 0xffff, 0xffff, 0xffff, 0x001b, 0x001c, 0x2797, 0x001d},
    {0xffff, 0xffff, 0xffff, 0xffff, 0x001e, 0x001f, 0x0020, 0x0021},
    {0xffff, 0xffff, 0xffff, 0xffff, 0x0022, 0x0023, 0x0024, 0x0025},
    {0xffff, 0xffff, 0xffff, 0xffff, 0x0026, 0x0027, 0x0028, 0x0029},
    {0xffff, 0xffff, 0xffff, 0xffff, 0x267e, 0x2796, 0x2795, 0x002a},
    {0xffff, 0xffff, 0xffff, 0xffff, 0x002b, 0x002c, 0x002d, 0x002e},
    {0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff},
    {0xffff, 0xffff, 0xffff, 0xffff, 0x306c, 0x305f, 0x3061, 0xffff},
};

static uint16_t unicode_sequence_00[] = {0xd83d, 0xde48, 0};          // 🙈
static uint16_t unicode_sequence_01[] = {0xd83d, 0xde49, 0};          // 🙉
static uint16_t unicode_sequence_02[] = {0xd83d, 0xde4a, 0};          // 🙊
static uint16_t unicode_sequence_03[] = {0xd83d, 0xde00, 0};          // 😀
static uint16_t unicode_sequence_04[] = {0xd83d, 0xde04, 0};          // 😄
static uint16_t unicode_sequence_05[] = {0xd83d, 0xde01, 0};          // 😁
static uint16_t unicode_sequence_06[] = {0xd83d, 0xde06, 0};          // 😆
static uint16_t unicode_sequence_07[] = {0xd83d, 0xde05, 0};          // 😆
static uint16_t unicode_sequence_08[] = {0xd83d, 0xde02, 0};          // 😆
static uint16_t unicode_sequence_09[] = {0xd83e, 0xdd23, 0};          // 🤣
static uint16_t unicode_sequence_0a[] = {0xd83d, 0xde2d, 0};          // 😭
static uint16_t unicode_sequence_0b[] = {0xd83d, 0xde09, 0};          // 😉
static uint16_t unicode_sequence_0c[] = {0xd83d, 0xde17, 0};          // 😗
static uint16_t unicode_sequence_0d[] = {0xd83d, 0xde1a, 0};          // 😚
static uint16_t unicode_sequence_0e[] = {0xd83d, 0xde18, 0};          // 😘
static uint16_t unicode_sequence_0f[] = {0xd83e, 0xdd70, 0};          // 🥰
static uint16_t unicode_sequence_10[] = {0xd83d, 0xde0d, 0};          // 😍
static uint16_t unicode_sequence_11[] = {0xd83e, 0xdd29, 0};          // 🤩
static uint16_t unicode_sequence_12[] = {0xd83e, 0xdd73, 0};          // 🥳
static uint16_t unicode_sequence_13[] = {0xd83e, 0xdee0, 0};          // 🫠
static uint16_t unicode_sequence_14[] = {0xd83d, 0xde43, 0};          // 🙃
static uint16_t unicode_sequence_15[] = {0xd83e, 0xdd72, 0};          // 🥲
static uint16_t unicode_sequence_16[] = {0xd83e, 0xdd79, 0};          // 🥹
static uint16_t unicode_sequence_17[] = {0xd83e, 0xdee1, 0};          // 🫡
static uint16_t unicode_sequence_18[] = {0xd83e, 0xdd14, 0};          // 🤔
static uint16_t unicode_sequence_19[] = {0xd83e, 0xdee2, 0};          // 🫢
static uint16_t unicode_sequence_1a[] = {0xd83d, 0xde31, 0};          // 😱
static uint16_t unicode_sequence_1b[] = {0xd83d, 0xdd25, 0};          // 🔥
static uint16_t unicode_sequence_1c[] = {0x2716, 0xfe0f, 0};          // ✖
static uint16_t unicode_sequence_1d[] = {0x0030, 0xfe0f, 0x20e3, 0};  // 0️⃣
static uint16_t unicode_sequence_1e[] = {0xd83d, 0xdd1f, 0};          // 🔟
static uint16_t unicode_sequence_1f[] = {0x0037, 0xfe0f, 0x20e3, 0};  // 7️⃣
static uint16_t unicode_sequence_20[] = {0x0034, 0xfe0f, 0x20e3, 0};  // 4️⃣
static uint16_t unicode_sequence_21[] = {0x0031, 0xfe0f, 0x20e3, 0};  // 1️⃣
static uint16_t unicode_sequence_22[] = {0x2764, 0xfe0f, 0};          // ❤️
static uint16_t unicode_sequence_23[] = {0x0038, 0xfe0f, 0x20e3, 0};  // 8️⃣
static uint16_t unicode_sequence_24[] = {0x0035, 0xfe0f, 0x20e3, 0};  // 5️⃣
static uint16_t unicode_sequence_25[] = {0x0032, 0xfe0f, 0x20e3, 0};  // 2️⃣
static uint16_t unicode_sequence_26[] = {0x2764, 0xfe0f, 0x200d,
                                         0xd83e, 0xde79, 0};  // ❤️‍🩹
static uint16_t unicode_sequence_27[] = {0x0039, 0xfe0f, 0x20e3, 0};  // 9️⃣
static uint16_t unicode_sequence_28[] = {0x0036, 0xfe0f, 0x20e3, 0};  // 6️⃣
static uint16_t unicode_sequence_29[] = {0x0033, 0xfe0f, 0x20e3, 0};  // 3️⃣
static uint16_t unicode_sequence_2a[] = {0xd83d, 0xdff0, 0};          // 🟰
static uint16_t unicode_sequence_2b[] = {0xd83d, 0xdc4c, 0};          // 👌
static uint16_t unicode_sequence_2c[] = {0xd83d, 0xde4f, 0};          // 🙏
static uint16_t unicode_sequence_2d[] = {0xd83d, 0xdc4d, 0};          // 👍
static uint16_t unicode_sequence_2e[] = {0xd83e, 0xdef5, 0};          // 🫵

static uint16_t* unicode_sequence[] = {
    unicode_sequence_00, unicode_sequence_01, unicode_sequence_02,
    unicode_sequence_03, unicode_sequence_04, unicode_sequence_05,
    unicode_sequence_06, unicode_sequence_07, unicode_sequence_08,
    unicode_sequence_09, unicode_sequence_0a, unicode_sequence_0b,
    unicode_sequence_0c, unicode_sequence_0d, unicode_sequence_0e,
    unicode_sequence_0f, unicode_sequence_10, unicode_sequence_11,
    unicode_sequence_12, unicode_sequence_13, unicode_sequence_14,
    unicode_sequence_15, unicode_sequence_16, unicode_sequence_17,
    unicode_sequence_18, unicode_sequence_19, unicode_sequence_1a,
    unicode_sequence_1b, unicode_sequence_1c, unicode_sequence_1d,
    unicode_sequence_1e, unicode_sequence_1f, unicode_sequence_20,
    unicode_sequence_21, unicode_sequence_22, unicode_sequence_23,
    unicode_sequence_24, unicode_sequence_25, unicode_sequence_26,
    unicode_sequence_27, unicode_sequence_28, unicode_sequence_29,
    unicode_sequence_2a, unicode_sequence_2b, unicode_sequence_2c,
    unicode_sequence_2d, unicode_sequence_2e,
};

static void message_reset(void) {
  for (int i = 0; i < REPORT_SIZE; ++i) {
	prev_key_message[i] = key_message[i];
    key_message[i] = 0;
    unicode_message[i] = 0;
  }
  key_index = KEYBOARD_REPORT_OFFSET;
  unicode_index = UNICODE_REPORT_OFFSET;
  key_message[0] = KEYBOARD_REPORT_ID;
  unicode_message[0] = UNICODE_REPORT_ID;
}

static void message_set_phantom_state(void) {
  for (int i = KEYBOARD_REPORT_OFFSET; i < REPORT_SIZE; ++i) {
    key_message[i] = 1;
  }
  key_index = REPORT_SIZE + 1;
  for (int i = UNICODE_REPORT_OFFSET; i < REPORT_SIZE; ++i) {
    unicode_message[i] = 0;
  }
  unicode_index = REPORT_SIZE + 1;
}

static void message_push_usage(uint8_t usage) {
  if (0xe0 <= usage && usage <= 0xe7) {
    // modifiers
    key_message[KEYBOARD_REPORT_MODIFIER_OFFSET] |= (1 << (usage & 7));
    return;
  }
  if (key_index == REPORT_SIZE) {
    message_set_phantom_state();
  } else if (key_index < REPORT_SIZE) {
    key_message[key_index++] = usage;
  }
}

// Experimental to send Unicode events over HID report.
// Unicode Page (0x10) is defined in the HID spec, but haven't used for
// keyboards and no operating system seems to support the case for now.
// You can handle this directly if your application can speak HID directly,
// e.g. web sites using WebHID.
// Unicode Page assumes the Unicode Standard, Version 1.1 that was the newest
// version when the usage page was defined, and 16bit code here is expected
// to be UCS-2. However, we may send UTF-16 here as a natural expansion.
static void message_push_unicode(uint16_t code) {
  if (unicode_index == REPORT_SIZE) {
    message_set_phantom_state();
  } else if (unicode_index < REPORT_SIZE) {
    unicode_message[unicode_index++] = code & 0xff;
    unicode_message[unicode_index++] = code >> 8;
  }
}

void hid_init(void) {
  if (!i2c_is_host()) {
    i2c_activate_host();
  }
  active = true;
  for (int i = 0; i < KEY_LINES; ++i) {
    prev_keys[i] = 0xff;
  }
}

void hid_update(const uint8_t* keys) {
  if (!active) {
    return;
  }
  message_reset();
  for (int i = 0; i < KEY_LINES; ++i) {
    for (int bit = 0; bit < KEY_COLUMNS; ++bit) {
      if ((keys[i] & (1 << bit)) == 0) {
        uint8_t usage = usage_id[i][bit];
        if (usage) {
          message_push_usage(usage);
        } else if (prev_keys[i] & (1 << bit)) {
          // Unicode sequence will be sent only on pushing edge.
          uint16_t code = unicode[i][bit];
          if (code < 0x0100) {
            for (int sequence = 0; unicode_sequence[code][sequence];
                 ++sequence) {
              message_push_unicode(unicode_sequence[code][sequence]);
            }
          } else if (code != 0xffff) {
            message_push_unicode(code);
          }
        }
      }
    }
    prev_keys[i] = keys[i];
  }
  bool changed = false;
  for (int i = 0; i < REPORT_SIZE; ++i) {
    if (prev_key_message[i] != key_message[i]) {
      changed = true;
      break;
    }
  }
  if (changed) {
    USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, key_message, REPORT_SIZE);
  }

  if (unicode_index > UNICODE_REPORT_OFFSET) {
    USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, unicode_message, REPORT_SIZE);
  }
}

void hid_deinit(void) { active = false; }

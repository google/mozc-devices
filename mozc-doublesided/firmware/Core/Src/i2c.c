// Copyright 2024 Google Inc.
// Use of this source code is governed by an Apache License that can be found in
// the LICENSE file.

#include "i2c.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "hid.h"
#include "led.h"
#include "main.h"

extern I2C_HandleTypeDef hi2c1;

enum {
  STATE_IDLE,
  STATE_LISTENING,
  STATE_WRITTEN,
  STATE_READ,
  STATE_HOST,
  STATE_INIT_HOST,
};

static volatile uint8_t state = STATE_IDLE;
static volatile uint8_t address = 0;
static volatile uint8_t commands[24];
static volatile uint8_t sw_pushed = 0xff;
static volatile uint8_t sw_current = 0xff;
static bool ready = false;
static uint8_t keys[26];
static uint8_t leds[26 * 24];

void HAL_I2C_AddrCallback(I2C_HandleTypeDef* hi2c, uint8_t TransferDirection,
                          uint16_t AddrMatchCode) {
  address = AddrMatchCode >> 1;
  if (TransferDirection == I2C_DIRECTION_RECEIVE) {
    HAL_I2C_Slave_Seq_Transmit_IT(hi2c, &sw_pushed, 1,
                                  I2C_FIRST_AND_LAST_FRAME);
  } else {
    if (address == 0x01) {
      HAL_I2C_Slave_Seq_Receive_IT(hi2c, commands, 1, I2C_FIRST_AND_LAST_FRAME);
    } else {
      HAL_I2C_Slave_Seq_Receive_IT(hi2c, commands, 24,
                                   I2C_FIRST_AND_LAST_FRAME);
    }
  }
}

void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef* I2cHandle) {
  state = STATE_READ;
}

void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef* I2cHandle) {
  state = STATE_WRITTEN;
}

void HAL_I2C_ErrorCallback(I2C_HandleTypeDef* hi2c) { state = STATE_IDLE; }

static void update_leds(uint8_t* data) {
  led_set(0, data[0], data[1], data[2]);
  led_set(1, data[3], data[4], data[5]);
  led_set(2, data[6], data[7], data[8]);
  led_set(3, data[9], data[10], data[11]);
  led_set(4, data[12], data[13], data[14]);
  led_set(5, data[15], data[16], data[17]);
  led_set(6, data[18], data[19], data[20]);
  led_set(7, data[21], data[22], data[23]);
  led_flush();
}

static void h2rgb(uint8_t h, uint8_t* r, uint8_t* g, uint8_t* b) {
  uint8_t i = h / 30;
  uint8_t k = (h % 30) * 6;
  uint8_t n = 180 - k;
  switch (i) {
    case 0:
      *r = 180;
      *g = k;
      *b = 180;
      break;
    case 1:
      *r = n;
      *g = 180;
      *b = 180;
      break;
    case 2:
      *r = 180;
      *g = 180;
      *b = k;
      break;
    case 3:
      *r = 180;
      *g = n;
      *b = 180;
      break;
    case 4:
      *r = k;
      *g = 180;
      *b = 180;
      break;
    case 5:
      *r = 180;
      *g = 180;
      *b = n;
      break;
  }
}

static void led_step(void) {
  uint8_t data[26 * 24];
  for (int i = 0; i < 26 * 24; ++i) {
    uint8_t half = leds[i] >> 1;
    uint8_t quarter = half >> 1;
    data[i] = half + quarter;
  }
  for (int i = 0; i < 26 * 24; ++i) {
    uint16_t v = data[i] >> 5;
    v += (data[(i + 26 * 24 - 24) % (26 * 24)] >> 1) +
         (data[(i + 24) % (26 * 24)] >> 1);
    v += (data[(i + 26 * 24 - 3) % (26 * 24)] >> 5) +
         (data[(i + 3) % (26 * 24)] >> 5);
    leds[i] = (v > 128) ? 128 : v;
  }
}

static void setup_pull(bool pullup) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = pullup ? GPIO_PULLUP : GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF1_I2C1;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
}

static void setup_host(void) {
  hi2c1.Init.Timing = 0x00101D2D;
  hi2c1.Init.OwnAddress1 = 0;
  HAL_I2C_Init(&hi2c1);

  setup_pull(true);
  state = STATE_HOST;
  uint8_t addr = 0xa0;
  for (int i = 0; i < 24; ++i) {
    commands[i] = 0;
  }
  while (GPIO_PIN_RESET == HAL_GPIO_ReadPin(RDYin_GPIO_Port, RDYin_Pin)) {
    HAL_StatusTypeDef s =
        HAL_I2C_Master_Transmit(&hi2c1, 1 << 1, &addr, 1, 100);
    if (s == HAL_OK) {
      HAL_Delay(50);
      HAL_I2C_Master_Transmit(&hi2c1, addr << 1, commands, 24, 100);
      addr++;
    }
  }
  for (int i = 0; i < 26; ++i) {
    keys[i] = 0xff;
    for (int j = 0; j < 24; ++j) {
      leds[i * 24 + j] = 0;
    }
  }
}

static void setup_client(uint8_t address) {
  hi2c1.Init.OwnAddress1 = address << 1;
  HAL_I2C_Init(&hi2c1);

  setup_pull(false);
}

void i2c_init(void) {
  HAL_GPIO_WritePin(RDYout_GPIO_Port, RDYout_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(COM1_GPIO_Port, COM1_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(COM2_GPIO_Port, COM2_Pin, GPIO_PIN_SET);
  const bool is_host = !HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin) &&
                       !HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin) &&
                       !HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin) &&
                       !HAL_GPIO_ReadPin(SW4_GPIO_Port, SW4_Pin);
  HAL_GPIO_WritePin(COM1_GPIO_Port, COM1_Pin, GPIO_PIN_SET);
  if (is_host) {
    setup_host();
  } else {
    setup_client(0x00);
  }
}

static void maybe_listen_client(void) {
  HAL_GPIO_WritePin(COM2_GPIO_Port, COM2_Pin, GPIO_PIN_RESET);
  uint8_t sw = HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin) << 4 |
               HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin) << 5 |
               HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin) << 6 |
               HAL_GPIO_ReadPin(SW4_GPIO_Port, SW4_Pin) << 7;
  HAL_GPIO_WritePin(COM2_GPIO_Port, COM2_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(COM1_GPIO_Port, COM1_Pin, GPIO_PIN_RESET);

  const bool ready_now =
      GPIO_PIN_SET == HAL_GPIO_ReadPin(RDYin_GPIO_Port, RDYin_Pin);
  if (ready != ready_now) {
    ready = ready_now;
    HAL_I2C_DisableListen_IT(&hi2c1);
    setup_client(ready ? 0x01 : 0x00);
    state = STATE_IDLE;
  }

  sw |= HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin) << 0 |
        HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin) << 1 |
        HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin) << 2 |
        HAL_GPIO_ReadPin(SW4_GPIO_Port, SW4_Pin) << 3;
  HAL_GPIO_WritePin(COM1_GPIO_Port, COM1_Pin, GPIO_PIN_SET);
  sw_current = sw;
  sw_pushed &= sw;

  if (state != STATE_LISTENING) {
    if (state == STATE_READ) {
      sw_pushed |= sw_current;
    } else if (state == STATE_WRITTEN) {
      if (address == 1) {
        uint8_t new_address = commands[0] & 0x7f;
        setup_client(new_address);
        HAL_GPIO_WritePin(RDYout_GPIO_Port, RDYout_Pin, GPIO_PIN_SET);
        if (commands[0] & 0x80) {
          for (uint8_t bit = 0; bit < 8; ++bit) {
            uint8_t v = new_address & (1 << bit) ? 255 : 0;
            led_set(bit, v, v, v);
          }
          led_flush();
        }
      } else {
        update_leds(commands);
      }
    }
    if (HAL_OK == HAL_I2C_EnableListen_IT(&hi2c1)) {
      state = STATE_LISTENING;
    }
  }
}

static void maybe_listen_host(void) {
  HAL_GPIO_WritePin(COM2_GPIO_Port, COM2_Pin, GPIO_PIN_RESET);
  keys[25] = HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin) << 4 |
             HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin) << 5 |
             HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin) << 6 |
             HAL_GPIO_ReadPin(SW4_GPIO_Port, SW4_Pin) << 7;
  HAL_GPIO_WritePin(COM2_GPIO_Port, COM2_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(COM1_GPIO_Port, COM1_Pin, GPIO_PIN_RESET);
  for (uint8_t addr = 0; addr < 25; ++addr) {
    HAL_I2C_Master_Receive(&hi2c1, (0x20 + addr) << 1, &keys[addr], 1, 100);
  }
  keys[25] |= HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin) << 0 |
              HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin) << 1 |
              HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin) << 2 |
              HAL_GPIO_ReadPin(SW4_GPIO_Port, SW4_Pin) << 3;
  HAL_GPIO_WritePin(COM1_GPIO_Port, COM1_Pin, GPIO_PIN_SET);

  hid_update(keys);

  led_step();

  static uint8_t h = 0;
  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;
  h2rgb(h, &r, &g, &b);
  h = (h + 1) % 180;

  for (int i = 0; i < 26; ++i) {
    uint8_t key = keys[i];
    uint8_t* led = &leds[i * 24];
    for (uint8_t mask = 0x01; mask != 0; mask <<= 1) {
      if (0 == (key & mask)) {
        led[0] = r;
        led[1] = g;
        led[2] = b;
      }
      led += 3;
    }
    if (i != 25) {
      HAL_I2C_Master_Transmit(&hi2c1, (0x20 + i) << 1, led - 24, 24, 100);
    } else {
      update_leds(led - 24);
    }
  }
}

bool i2c_is_host(void) { return state == STATE_HOST; }

void i2c_activate_host(void) { state = STATE_INIT_HOST; }

void i2c_maybe_listen(void) {
  if (state == STATE_INIT_HOST) {
    setup_host();
  }
  if (state == STATE_HOST) {
    maybe_listen_host();
  } else {
    maybe_listen_client();
  }
}

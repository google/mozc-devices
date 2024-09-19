// Copyright 2024 Google Inc.
// Use of this source code is governed by an Apache License that can be found in
// the LICENSE file.

#include "led.h"

#include "main.h"

extern SPI_HandleTypeDef hspi1;

#define RESET_COUNT 16
#define LED_COUNT 8
#define DATA_LENGTH 6
#define DMA_BUFFER_SIZE (RESET_COUNT + LED_COUNT * DATA_LENGTH + 1) << 1

// 0xe: 1110 - HIGH
// 0x8: 1000 - LOW
static uint16_t dma_buffer[DMA_BUFFER_SIZE] = {
    0,      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // RESET
    0,      0, 0, 0, 0, 0,                                // LED 0
    0,      0, 0, 0, 0, 0,                                // LED 1
    0,      0, 0, 0, 0, 0,                                // LED 2
    0,      0, 0, 0, 0, 0,                                // LED 3
    0,      0, 0, 0, 0, 0,                                // LED 4
    0,      0, 0, 0, 0, 0,                                // LED 5
    0,      0, 0, 0, 0, 0,                                // LED 6
    0,      0, 0, 0, 0, 0,                                // LED 7
    0xffff,                                               // EOD
};

static uint32_t to_spi_value(uint8_t value) {
  uint32_t spi_value = 0;
  for (uint8_t bit_mask = 0x80; bit_mask != 0; bit_mask >>= 1) {
    spi_value <<= 4;
    if (value & bit_mask) {
      spi_value |= 0xe;
    } else {
      spi_value |= 0x8;
    }
  }
  return spi_value;
}

void set_spi_value(uint8_t offset, uint32_t value) {
  dma_buffer[RESET_COUNT + offset * 2 + 0] = value >> 16;
  dma_buffer[RESET_COUNT + offset * 2 + 1] = value & 0xffff;
}

void led_set(uint8_t index, uint8_t r, uint8_t g, uint8_t b) {
  set_spi_value(index * 3 + 0, to_spi_value(g));
  set_spi_value(index * 3 + 1, to_spi_value(r));
  set_spi_value(index * 3 + 2, to_spi_value(b));
}

void led_flush(void) {
  HAL_SPI_Transmit_DMA(&hspi1, (uint8_t *)dma_buffer, DMA_BUFFER_SIZE);
}

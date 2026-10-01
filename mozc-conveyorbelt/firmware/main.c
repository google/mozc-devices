// Copyright 2026 Google Inc.
// Use of this source code is governed by an Apache License that can be found
// in the LICENSE file.

#include "ch559.h"
#include "flash.h"
#include "gpio.h"
#include "led.h"
#include "serial.h"
#include "switches.h"
#include "timer3.h"
#include "usb/ble/ble_hid_peripheral.h"
#include "usb/usb_host.h"

#define BLE_PASSKEY 738291
#define FLASH_MAGIC 0x4d5a4331  // "MZC1"
#define FLASH_OFFSET_BOND 4

enum {
  APPEARANCE_KEYBOARD = 0x03c1,
  HID_REPORT_LEN      = 8,
};

// HID Boot Keyboard Report Map (Input only; no LED output report).
static const uint8_t HID_REPORT_MAP[] = {
    0x05, 0x01,  // usage page (desktop)
    0x09, 0x06,  // usage (keyboard)
    0xa1, 0x01,  // collection (application)
    0x05, 0x07,  // usage page (key codes)
    0x19, 0xe0,  // usage minimum (224 / left control)
    0x29, 0xe7,  // usage maximum (231 / right gui)
    0x15, 0x00,  // logical minimum (0)
    0x25, 0x01,  // logical maximum (1)
    0x75, 0x01,  // report size (1)
    0x95, 0x08,  // report count (8)
    0x81, 0x02,  // input (modifiers byte)
    0x95, 0x01,  // report count (1)
    0x75, 0x08,  // report size (8)
    0x81, 0x03,  // input constant (reserved byte)
    0x95, 0x06,  // report count (6)
    0x75, 0x08,  // report size (8)
    0x15, 0x00,  // logical minimum (0)
    0x25, 0x65,  // logical maximum (101)
    0x05, 0x07,  // usage page (key codes)
    0x19, 0x00,  // usage minimum (0)
    0x29, 0x65,  // usage maximum (101)
    0x81, 0x00,  // input (key array)
    0xc0,        // end collection
};

static void on_ready(void) {
  Serial.println("advertising");
}

static void on_connected(void) {
  Serial.println("connected");
}

static bool notify_on;
static uint8_t last_report[HID_REPORT_LEN];

static void on_disconnected(void) {
  Serial.println("disconnected, re-advertising");
  notify_on = false;
  for (uint8_t i = 0; i < HID_REPORT_LEN; ++i) {
    last_report[i] = 0;
  }
}

static void on_notify_enabled(bool on) {
  Serial.println(on ? "notify: ON" : "notify: OFF");
  notify_on = on;
}

static uint8_t on_battery_level(void) {
  // No real battery on a USB-powered CH559 demo; report a fixed level so
  // the host shows a plausible value.
  return 100;
}

static void on_sent(void) {
}

static bool on_load_bond(struct smp_bond_info* bond) {
  if (!flash_read(FLASH_OFFSET_BOND, (uint8_t*)bond, sizeof(*bond))) {
    return false;
  }
  bool all_zero = true;
  bool all_ff = true;
  for (uint8_t i = 0; i < sizeof(*bond); i++) {
    uint8_t b = ((const uint8_t*)bond)[i];
    if (b != 0) {
      all_zero = false;
    }
    if (b != 0xff) {
      all_ff = false;
    }
  }
  if (all_zero || all_ff) {
    return false;
  }
  Serial.println("Bonding info loaded from flash");
  return true;
}

static void on_save_bond(const struct smp_bond_info* bond) {
  Serial.println("Saving bonding info to flash...");
  if (flash_write(FLASH_OFFSET_BOND, (const uint8_t*)bond, sizeof(*bond))) {
    Serial.println("Saved!");
  } else {
    Serial.println("Flash write failed!");
  }
}

void main(void) {
  initialize();

  // Initialize serial and print boot message.
  serial_init();
  Serial.println("Booting mozc...");

  // Initialize Data Flash.
  flash_init(FLASH_MAGIC, true);

  // Initialize LED on Port 1, Pin 4 (P1.4, standard for CH559 EVT), Active HIGH.
  led_init(1, 4, HIGH);
  led_mode(L_BLINK);

  // Initialize key switches.
  switches_init();

  // Initialize USB host stack to implement BLE HID over USB-BLE dongle.
  static const struct ble_hid_peripheral hid = {
      .local_name = "Gboard DIY Device",
      .appearance = APPEARANCE_KEYBOARD,
      .manufacturer = "Gboard DIY team",
      .model = "Gboard DIY Device",
      .pnp_id = {BLE_VID_SOURCE_USB_IF, 0xffff, 0x0001, 0x0100},
      .report_map = HID_REPORT_MAP,
      .report_map_len = sizeof(HID_REPORT_MAP),
      .report_len = HID_REPORT_LEN,
      .passkey = BLE_PASSKEY,
      .battery_level = on_battery_level,
      .ready = on_ready,
      .connected = on_connected,
      .disconnected = on_disconnected,
      .notify_enabled = on_notify_enabled,
      .sent = on_sent,
      .load_bond = on_load_bond,
      .save_bond = on_save_bond,
  };
  ble_hid_peripheral_init(&hid, USE_HUB0);
  // TODO: the library sometimes fails to recognize a dongle plugged in at
  // power-on; force a bus reset as a workaround until that's fixed.
  usb_host_reset();

  for (;;) {
    led_poll();
    uint8_t report[HID_REPORT_LEN];
    switches_poll(report, HID_REPORT_LEN);
    if (notify_on) {
      bool changed = false;
      for (uint8_t i = 0; i < HID_REPORT_LEN; ++i) {
        if (report[i] != last_report[i]) {
          changed = true;
          break;
        }
      }
      if (changed && ble_hid_peripheral_send_report(report, HID_REPORT_LEN)) {
        for (uint8_t i = 0; i < HID_REPORT_LEN; ++i) {
          last_report[i] = report[i];
        }
        Serial.printf("Report: mod=%02x keys=[", report[0]);
        for (uint8_t i = 2; i < HID_REPORT_LEN; ++i) {
          Serial.printf("%02x ", report[i]);
        }
        Serial.println("]");
      }
    }
    ble_hid_peripheral_poll();
  }
}

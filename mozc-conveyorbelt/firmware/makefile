# Copyright 2026 Google Inc.
# Use of this source code is governed by an Apache License that can be found
# in the LICENSE file.

CHLIB_DIR   = chlib
CHLIB_URL   = https://github.com/toyoshim/chlib.git
CHLIB_REV   = 9f7833caf39706684c55b5e970ffb72ae7a807c6

ifeq ($(wildcard $(CHLIB_DIR)/src),)
  ifeq ($(filter clean distclean,$(MAKECMDGOALS)),)
    $(info Checking out $(CHLIB_DIR) at $(CHLIB_REV)...)
    CLONE_RESULT := $(shell git clone $(CHLIB_URL) $(CHLIB_DIR) && git -C $(CHLIB_DIR) checkout -q $(CHLIB_REV) && echo ok)
    ifneq ($(CLONE_RESULT),ok)
      $(error Failed to check out $(CHLIB_DIR) from $(CHLIB_URL))
    endif
  endif
endif

CC          = sdcc
OBJCOPY     = sdobjcopy
FLASHER_DIR = ch559flasher
FLASHER_URL = https://github.com/toyoshim/ch559flasher.git
FLASHER     := $(shell which ch559flasher 2>/dev/null || which $(FLASHER_DIR)/target/release/ch559flasher 2>/dev/null || which $(HOME)/.cargo/bin/ch559flasher 2>/dev/null)

TARGET      = mozc
INCLUDES    = -I. -I$(CHLIB_DIR)/src
CFLAGS      = -V -mmcs51 --model-large --xram-size 0x1800 --xram-loc 0x0000 \
              --code-size 0xec00 --stack-auto --Werror --opt-code-speed $(INCLUDES)

SRC_DIRS    = . \
              $(CHLIB_DIR)/src \
              $(CHLIB_DIR)/src/ble \
              $(CHLIB_DIR)/src/crypto \
              $(CHLIB_DIR)/src/usb \
              $(CHLIB_DIR)/src/usb/ble

vpath %.c $(SRC_DIRS)

OBJS        = main.rel switches.rel \
              ch559.rel gpio.rel led.rel serial.rel timer3.rel flash.rel \
              hci.rel l2cap.rel att.rel smp.rel \
              ble_peripheral.rel ble_hid_peripheral.rel \
              usb_host.rel \
              aes.rel

BUILD_DIR   = build
BUILD_OBJS  = $(addprefix $(BUILD_DIR)/, $(OBJS))
HEADERS     = $(wildcard *.h $(CHLIB_DIR)/src/*.h $(CHLIB_DIR)/src/*/*.h $(CHLIB_DIR)/src/*/*/*.h)

.PHONY: all clean distclean program run

all: $(TARGET).bin

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.rel: %.c $(HEADERS) | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD_DIR)/$(TARGET).ihx: $(BUILD_OBJS)
	$(CC) $(CFLAGS) $(BUILD_OBJS) -o $@

%.bin: $(BUILD_DIR)/%.ihx
	$(OBJCOPY) -I ihex -O binary $< $@

program: $(TARGET).bin
ifeq ($(FLASHER),)
	@which cargo >/dev/null 2>&1 || (echo "Error: ch559flasher is not found and cargo is not available. Please install Rust/cargo, or use official tools (e.g. WCHISPTool)." && exit 1)
	@if [ ! -d $(FLASHER_DIR) ]; then \
		echo "Cloning $(FLASHER_URL)..."; \
		git clone $(FLASHER_URL) $(FLASHER_DIR); \
	fi
	cargo build --release --manifest-path $(FLASHER_DIR)/Cargo.toml
	$(FLASHER_DIR)/target/release/ch559flasher -w $(TARGET).bin
else
	$(FLASHER) -w $(TARGET).bin
endif

run: program
ifeq ($(FLASHER),)
	$(FLASHER_DIR)/target/release/ch559flasher -b
else
	$(FLASHER) -b
endif

clean:
	rm -rf $(BUILD_DIR) $(TARGET).bin

distclean: clean
	rm -rf $(CHLIB_DIR) $(FLASHER_DIR)

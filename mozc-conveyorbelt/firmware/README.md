# Firmware Development Guide

For the entire keyboard assembly, please refer to the
[Build Guide](../buildguide.md).

## File List

-   `prebuilt/` : Pre-built firmware
-   `keymap.h` : Keymap definitions
-   `main.c` : Source file for the main chip
-   `makefile` : Build configuration
-   `switches.h` / `switches.c` : Source files for key switch and shift register
    control
-   `chlib/` : Common library (automatically fetched during build)

## Pre-built Firmware

Pre-built firmware (`mozc.bin`) is located under `prebuilt/`, so you can use it
directly if no modifications are needed.

Press and hold `SW4` (BOOT switch) on the board while connecting the USB cable
to enter bootloader mode, and flash using
[ch559flasher](https://github.com/toyoshim/ch559flasher):

```sh
ch559flasher -w prebuilt/mozc.bin
ch559flasher -b
```

If flashing does not work (e.g. device is not recognized, USB driver setup is
required) or installing the tool is difficult, please flash using the official
WCH development tool
([WCHISPTool](http://www.wch.cn/downloads/WCHISPTool_Setup_exe.html)).

## Guide to Developing Your Own Firmware

### Build Environment Setup

Firmware is compiled with [SDCC](https://sdcc.sourceforge.net/) and flashed with
[ch559flasher](https://github.com/toyoshim/ch559flasher).

-   **Debian / Ubuntu**:

    ```sh
    sudo apt install sdcc binutils
    ```
-   **Windows**:

    ```powershell
    winget install sdcc
    ```

Manual installation of ch559flasher (requires Rust / Cargo):

```sh
cargo install --git https://github.com/toyoshim/ch559flasher.git
```

*   If not installed, `make program` will also attempt to fetch it
    automatically.

### Build and Flash

Running `make` automatically clones the required library (`chlib`) and builds
the firmware. If `ch559flasher` is not installed, running `make program` will
attempt to fetch it automatically.

```sh
# Build
make

# Flash (execute while USB is connected with SW4 held down)
make program

# Flash and run
make run
```

### Standard Output

Debug output is emitted from UART0 (TXD: P0.3) of the CH559L at 115200bps. You
can inspect logs by connecting a serial converter to the `TXD` land on the
board.

### Customizing the Keymap

To modify the key layout, edit the `keymap` array in `keymap.h`. Each key entry
is assigned a HID Usage ID and a Shift flag.

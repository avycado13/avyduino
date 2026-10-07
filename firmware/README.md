# Avyduino firmware

This board uses an **ATmega328P at 16 MHz** (Y2 in the schematic), a CH340G USB-to-UART bridge (its 12 MHz crystal is separate), and a 6-pin ICSP header. It is compatible with the **Arduino Uno** board definition. The bootloader is the official Uno **Optiboot** supplied by the `arduino:avr` core; no custom bootloader is needed. `firmware.ino` is a bring-up sketch: it echoes USB serial input at 115200 baud and toggles D13 every 500 ms. For a visible heartbeat, connect an external LED **with a current-limiting resistor** from D13 to GND; don't assume an onboard D13 LED.

## First-time programming (blank ATmega328P)

1. Install [Arduino CLI](https://arduino.github.io/arduino-cli/latest/installation/) and run `cd firmware && make core` (or install `arduino:avr` using the Arduino IDE Boards Manager).
2. Assemble and power the board. Connect a 5 V-compatible ISP programmer to the **ATmega328P's** 6-pin ICSP header: MISO, MOSI, SCK, RESET, 5V and GND. Check the physical header orientation against the PCB/schematic. Do not drive the target from two power supplies without checking their compatibility.
3. Run `make burn PROGRAMMER=usbasp` from `firmware/` (replace `usbasp` with your programmer's Arduino CLI ID). This writes Uno Optiboot and the Uno fuse settings. **Only do this if the ATmega's 16 MHz crystal and its load capacitors are populated**: the external-clock fuses can make ISP programming appear to stop working if the oscillator is absent. Bootloader burning is not done over the CH340G USB port.

## Upload and test

1. Connect USB-C and find the CH340G serial port using `arduino-cli board list` (e.g. `/dev/ttyUSB0`, `/dev/cu.wchusbserial*`, or `COM3`). On some systems the CH340 driver must be installed separately.
2. From `firmware/`, run `make upload PORT=/dev/ttyUSB0` (substitute your port). This builds for `arduino:avr:uno` and uploads at the Uno's bootloader baud rate. The programmer is **not** needed for this step. Alternatively open `firmware.ino` in Arduino IDE, select **Arduino Uno** and the CH340 serial port, and click Upload.
3. Open a serial monitor at **115200 baud**. Resetting or opening the port should print `Avyduino ready...`; text sent to it is echoed back. D13 changes state twice per second. If a terminal's local echo is enabled, characters may appear twice.

If USB upload fails, verify power, CH340 enumeration, that the bootloader was burned, and that the CH340 TX/RX and DTR-to-RESET connections are working. An ISP can also upload sketches directly, but doing so overwrites the bootloader; burn it again to restore USB uploads.

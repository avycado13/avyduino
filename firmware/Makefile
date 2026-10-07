# Requires arduino-cli and the arduino:avr core (make core).
CLI ?= arduino-cli
FQBN := arduino:avr:uno
PROGRAMMER ?= usbasp
BUILD_DIR := .build

.PHONY: core compile burn upload clean

core:
	$(CLI) core update-index
	$(CLI) core install arduino:avr

compile:
	$(CLI) compile --fqbn $(FQBN) --output-dir $(BUILD_DIR) .

# The first flash must use an ISP programmer connected to the 6-pin ICSP header.
# WARNING: burning the bootloader also sets the Uno's external-clock fuses.
burn:
	$(CLI) burn-bootloader --fqbn $(FQBN) --programmer $(PROGRAMMER)

# Subsequent uploads go via the CH340G USB serial port and the Uno bootloader.
upload: compile
	@test -n "$(PORT)" || { echo 'Set PORT (e.g. make upload PORT=/dev/ttyUSB0)' >&2; exit 1; }
	$(CLI) upload --fqbn $(FQBN) --port "$(PORT)" --input-dir $(BUILD_DIR) .

clean:
	rm -rf $(BUILD_DIR)

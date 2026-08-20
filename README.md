# Shift Register LED Matrix Controller with PCB Design

ESP32-controlled 8x8 LED matrix using two 74HCT595 shift registers, AO3401A high-side row drivers, and a ULN2803C low-side column driver.

## Features
- Manual GPIO-register bit-banged serial interface (DATA/CLOCK/LATCH)
- 16-bit cascaded shift-register control
- 8x8 framebuffer
- Multiplexed row scanning
- Basic 5x7 font and scrolling-text framework
- Timer-driven refresh architecture
- One-layer PCB design guidance

## Hardware
- ESP32 development board
- 2x 74HCT595
- 1x ULN2803C
- 8x AO3401A P-channel MOSFET
- Common-anode 8x8 LED matrix
- 8x 220 ohm LED resistors
- 8x 10k ohm MOSFET gate pull-ups
- 2x 100 nF decoupling capacitors
- 10 uF + 100 uF bulk capacitors

## Pin mapping
- GPIO23: DATA
- GPIO18: CLOCK
- GPIO5: LATCH

## Important
The hardware folder contains design notes and placeholders rather than claiming a fabricated PCB or passed DRC. Verify the exact LED-matrix pinout and component footprints before fabrication.

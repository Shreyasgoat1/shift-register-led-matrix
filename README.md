# Shift Register LED Matrix Controller with PCB Design

An ESP32-based 8×8 LED Matrix Controller using two chained 74HCT595 shift registers, ULN2803C current sinking, P-channel MOSFET row drivers, and a custom 1-layer PCB. The project demonstrates low-level GPIO control, bit-banged SPI communication, multiplexed LED scanning, framebuffer management, scrolling text, and embedded PCB design.

## Features

* ESP32-based LED matrix controller
* 8×8 LED matrix display
* Two chained 74HCT595 shift registers
* Manual SPI-style bit-banging without `SPI.h` or `shiftOut()`
* Direct ESP32 GPIO register manipulation
* ULN2803C for column current sinking
* P-channel MOSFETs for row switching
* 220 Ω LED current-limiting resistors
* 100 nF decoupling capacitors for shift registers
* Multiplexed row-scanning display
* Static framebuffer using `uint8_t framebuffer[8]`
* 5×7 font support
* Scrolling text
* Simple LED animations
* Timer-based display refresh
* Custom 1-layer PCB design
* DRC and Gerber validation workflow
* Modular ESP-IDF firmware structure

## Project Structure

```text
shift-register-led-matrix/
│
├── README.md
│
├── hardware/
│   ├── schematic/
│   │   └── schematic_design.md
│   │
│   ├── pcb/
│   │   └── pcb_design.md
│   │
│   ├── gerbers/
│   │   └── gerber_export_checklist.md
│   │
│   └── bom/
│       └── BOM.csv
│
├── firmware/
│   ├── main/
│   │   ├── main.c
│   │   ├── shift_register.c
│   │   ├── shift_register.h
│   │   ├── display.c
│   │   ├── display.h
│   │   ├── font.c
│   │   └── font.h
│   │
│   ├── CMakeLists.txt
│   └── sdkconfig.defaults
│
├── docs/
│   ├── circuit-design.md
│   ├── pcb-design.md
│   └── validation.md
│
└── images/
    ├── schematic.png
    ├── pcb.png
    └── prototype.jpg
```

## Installation

### Hardware Requirements

* ESP32 development board
* 8×8 common-anode LED matrix
* 2 × 74HCT595 shift registers
* ULN2803C Darlington transistor array
* 8 × AO3401A P-channel MOSFETs
* 8 × 220 Ω resistors
* 8 × 10 kΩ MOSFET gate pull-up resistors
* 2 × 100 nF ceramic capacitors
* 10 µF capacitor
* 100 µF capacitor
* 5 V power supply
* Custom 1-layer PCB
* Connecting headers and wires

### Software Requirements

Install:

* ESP-IDF
* VS Code with ESP-IDF extension or ESP-IDF command-line tools
* EasyEDA for schematic and PCB design

### Clone the Repository

```bash
git clone https://github.com/yourusername/shift-register-led-matrix.git
cd shift-register-led-matrix
```

### Configure ESP-IDF

Set the ESP32 target:

```bash
idf.py set-target esp32
```

Build the project:

```bash
idf.py build
```

Flash the firmware:

```bash
idf.py flash
```

Monitor the serial output:

```bash
idf.py monitor
```

Or flash and monitor together:

```bash
idf.py flash monitor
```

## Running Algorithm

The system uses multiplexing to display an 8×8 LED matrix.

### Step 1 — Initialize GPIO

The ESP32 configures three GPIO pins:

```text
GPIO23 → DATA
GPIO18 → CLOCK
GPIO5  → LATCH
```

These signals control the chained 74HCT595 shift registers.

### Step 2 — Prepare Framebuffer

The display uses:

```c
uint8_t framebuffer[8];
```

Each byte represents one row of the LED matrix.

```text
Bit 7 Bit 6 Bit 5 Bit 4 Bit 3 Bit 2 Bit 1 Bit 0
  ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓
 C7    C6    C5    C4    C3    C2    C1    C0
```

### Step 3 — Shift Data

The ESP32 manually generates the DATA and CLOCK signals.

```text
DATA → set bit
CLOCK → HIGH
CLOCK → LOW
```

The 74HCT595 captures the data on the clock edge.

### Step 4 — Transfer Data to Outputs

After all 16 bits are shifted, the ESP32 generates a LATCH pulse.

```text
16 bits shifted
       ↓
    LATCH
       ↓
Outputs updated
```

### Step 5 — Turn Off Current Row

The currently active row is disabled before changing the display data.

This reduces LED ghosting.

### Step 6 — Select Next Row

One row is activated using the P-channel MOSFET row driver.

At the same time, the corresponding framebuffer byte controls the column LEDs through the ULN2803C.

### Step 7 — Repeat Quickly

The controller continuously scans:

```text
Row 0
 ↓
Row 1
 ↓
Row 2
 ↓
Row 3
 ↓
Row 4
 ↓
Row 5
 ↓
Row 6
 ↓
Row 7
 ↓
Repeat
```

Because the scanning is fast enough, persistence of vision makes the matrix appear continuously illuminated.

### Step 8 — Scrolling Text

The font is stored as constant data in flash memory.

The framebuffer is shifted periodically:

```text
HELLO
 ↓
ELLO
 ↓
LLO
 ↓
LO
 ↓
O
```

New font columns are inserted as the text moves across the display.

## Technologies Used

### Hardware

* ESP32
* 74HCT595 shift registers
* ULN2803C
* AO3401A P-channel MOSFET
* 8×8 LED matrix
* Custom 1-layer PCB

### Firmware

* C
* ESP-IDF
* FreeRTOS
* ESP32 GPIO registers
* Hardware/ESP timer
* Bit-banged SPI
* Framebuffer-based display control

### PCB Design

* EasyEDA
* Schematic capture
* Single-layer PCB routing
* Design Rule Check (DRC)
* Gerber generation

## Current Progress

### Completed

* [x] System architecture designed
* [x] Component selection completed
* [x] LED current-limiting resistor calculation
* [x] 74HCT595 chain design
* [x] ULN2803C column-driver design
* [x] MOSFET row-driver design
* [x] ESP32 DATA/CLOCK/LATCH interface defined
* [x] Framebuffer architecture defined
* [x] Bit-banged SPI approach implemented
* [x] Multiplexing algorithm defined
* [x] Scrolling-text architecture defined
* [x] Project documentation structure created

### In Progress

* [ ] Complete EasyEDA schematic
* [ ] Complete 1-layer PCB routing
* [ ] Verify PCB footprints
* [ ] Run final DRC
* [ ] Generate production Gerbers
* [ ] Fabricate PCB
* [ ] Assemble hardware
* [ ] Test LED current and multiplexing
* [ ] Verify scrolling text on physical hardware

## Feature Improvements

Future versions can include:

1. **Wireless Control**

   * Add Wi-Fi control through the ESP32.
   * Create a web interface for changing displayed text.

2. **Bluetooth Control**

   * Send messages to the LED matrix from a smartphone.

3. **Brightness Control**

   * Implement PWM-based brightness control.

4. **More Animations**

   * Add scrolling effects, blinking, transitions, and graphical animations.

5. **Multiple LED Matrices**

   * Chain multiple 8×8 matrices to create a larger display.

6. **Real-Time Clock**

   * Display time, date, and other information.

7. **Sensor Integration**

   * Display temperature, humidity, or other sensor readings.

8. **Improved PCB**

   * Develop a compact 2-layer PCB for easier routing and improved power distribution.

9. **Modular Connectors**

   * Add dedicated connectors for the LED matrix, ESP32, and external power.

10. **Display Configuration**

* Allow users to change text, animation speed, brightness, and display mode through a web interface.

## Project Goal

The main goal of this project is to understand the complete embedded-system development process:

```text
Circuit Design
      ↓
Schematic
      ↓
PCB Design
      ↓
Firmware Development
      ↓
Low-Level GPIO Control
      ↓
LED Multiplexing
      ↓
Testing & Debugging
      ↓
Gerber Generation
      ↓
PCB Fabrication
```

This project combines **embedded C programming, ESP32, digital electronics, shift registers, LED multiplexing, and PCB design** into one practical system.

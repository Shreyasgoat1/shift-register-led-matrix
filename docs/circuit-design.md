# Circuit Design

Recommended architecture:
ESP32 -> 74HCT595 #1 -> 74HCT595 #2 -> drivers -> 8x8 common-anode matrix.

74HCT595 #1 controls eight AO3401A P-MOSFET row drivers. 74HCT595 #2 controls the eight ULN2803C column sinks.

Use 220 ohm series resistors for the eight column paths as a starting point, 10k gate pull-ups for each P-MOSFET, and 100nF ceramic decoupling at each 74HCT595. Add 10uF and 100uF bulk capacitance near the 5V input.

Verify the exact matrix pinout and LED Vf before fabrication.

# PCB Design Guidance

For a one-layer board, route the main 5V/GND rails first, then LED-current paths, then logic signals. Start with about 1.0 mm for main power and 0.20-0.25 mm for logic, then check the fabricator's current/clearance limits.

Use through-hole parts or 0-ohm jumpers where a crossover is unavoidable. Keep each 100nF capacitor close to its shift-register VCC/GND pins.

Do not claim DRC passed until the actual PCB is routed and checked.

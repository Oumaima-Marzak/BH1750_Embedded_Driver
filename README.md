# BH1750
## What's BH1750?

The BH1750 is a digital light intensity sensor that measures the amount of ambient light (illuminance) in lux (lx), the same unit the human eye perceives brightness. It communicates with microcontrollers like Arduino, ESP32, or STM32 through the I²C interface, making it very easy to use.

The sensor converts light levels directly into a digital value, no need for manual calibration or complex calculations. It automatically adjusts for different lighting conditions, from very dim to bright sunlight. This makes it useful for smart lighting systems, displays that adjust brightness automatically, and environmental monitoring.

### Key Features

| Feature               | Description                         |
| --------------------- | ----------------------------------- |
| **Measurement range** | 1 – 65,535 lux                      |
| **Interface**         | I²C (two addresses: 0x23 or 0x5C)   |
| **Resolution**        | Up to 0.5 lx                        |
| **ADC**               | 16-bit built-in converter           |
| **Power consumption** | Very low, ideal for battery systems |
| **Modes**             | Continuous and One-time             |
| **Form factor**       | Compact, easy to integrate          |


## Understanding Light Measurement
### What's Lux?

Lux (lx) is the unit that measures illuminance, meaning how much light falls on a surface. It tells how bright an area is as seen by the human eye, the higher the lux value, the brighter the light.

| Light Source / Environment | Approx. Lux       | Description        |
| -------------------------- | ----------------- | ------------------ |
| Moonless night sky         | 0.001 lx          | Very dark          |
| Full moon                  | 0.2–1 lx          | Dim natural light  |
| Living room lamp           | 50–200 lx         | Comfortable indoor |
| Office / classroom         | 300–700 lx        | Normal work light  |
| Cloudy daylight            | 1,000–5,000 lx    | Bright outdoor     |
| Direct sunlight            | 30,000–100,000 lx | Extremely bright   |


### How BH1750 mesures light?

The BH1750 measures light using a photodiode, a tiny component that converts light energy into an electrical current.
Inside the sensor, this current is processed by a built-in 16-bit analog-to-digital converter (ADC), which transforms the light level into a digital value.
The sensor automatically handles calibration and temperature compensation, so it gives readings that are already very close to real lux values.
When the microcontroller reads the data through the I²C interface, it receives a 16-bit raw number that represents the brightness.
To convert this number into lux, you simply apply a fixed scaling factor (as recommended in the datasheet): lux = raw_value / 1.2;

## Measurement Modes
### Mode Descriptions

The BH1750 offers several measurement modes that balance speed, accuracy, and power consumption.
You can choose between continuous and one-time modes, and between low or high resolution.

| Mode | Type       | Resolution | Measurement Time | Description             |
| ---- | ---------- | ---------- | ---------------- | ----------------------- |
| 0x10 | Continuous | 1 lx       | ~120 ms          | Continuous high-res     |
| 0x11 | Continuous | 0.5 lx     | ~120 ms          | Higher precision        |
| 0x13 | Continuous | 4 lx       | ~16 ms           | Low-res, fast updates   |
| 0x20 | One-time   | 1 lx       | ~120 ms          | Single read, power down |
| 0x21 | One-time   | 0.5 lx     | ~120 ms          | Single precise read     |
| 0x23 | One-time   | 4 lx       | ~16 ms           | Single fast read        |

- Continuous → keeps measuring, best for real-time data
- One-time → measures once, then sleeps (low power)
- H-Resolution → slower but accurate
- L-Resolution → faster but coarse

### Resolution

Resolution describes how small of a change in light the sensor can detect.
It’s basically the smallest step between two readings that the BH1750 can distinguish.

| Resolution | Meaning                  | Example                |
| ---------- | ------------------------ | ---------------------- |
| **1 lx**   | Detects 1-lux changes    | 100 → 101 lx visible   |
| **0.5 lx** | Detects half-lux changes | High precision         |
| **4 lx**   | Detects 4-lux steps      | Fast but less detailed |

Lower number (0.5 lx) → higher precision, slower measurement.
Higher number (4 lx) → lower precision, faster response.

### Adjustable Measurement Time and Sensitivity

The BH1750 allows you to adjust the measurement time, which changes how long the sensor collects light before giving a reading.
This feature lets you balance accuracy, response speed, and light range depending on your project needs.

| Condition            | Recommended Adjustment   |
| -------------------- | ------------------------ |
| Very bright light    | Shorter measurement time |
| Very dark light      | Longer measurement time  |
| Need faster refresh  | Decrease MTreg           |
| Need higher accuracy | Increase MTreg           |

For example:
- Increasing MTreg → longer integration → higher sensitivity.
- Decreasing MTreg → shorter integration → lower sensitivity.

## I²C Communication Interface

The BH1750 communicates with microcontrollers through the I²C protocol, a simple two-wire bus using:

- SCL (Serial Clock): generated by the microcontroller
- SDA (Serial Data): used to send and receive data

The sensor has two possible I²C addresses depending on how the ADDR pin is connected:

- 0x23 → when ADDR pin is LOW or not connected
- 0x5C → when ADDR pin is HIGH (connected to VCC)

### Command Set Overview

The BH1750 operates by receiving 1-byte command codes from the microcontroller. Each command tells it what mode or operation to perform.

| Command | Function           | Description          |
| ------- | ------------------ | -------------------- |
| `0x00`  | Power Down         | Turn off sensor      |
| `0x01`  | Power On           | Wake up sensor       |
| `0x07`  | Reset              | Clear data registers |
| `0x10`  | Continuous H-Res   | 1 lx, ~120 ms        |
| `0x11`  | Continuous H-Res 2 | 0.5 lx, ~120 ms      |
| `0x13`  | Continuous L-Res   | 4 lx, ~16 ms         |
| `0x20`  | One-Time H-Res     | 1 lx, ~120 ms        |
| `0x21`  | One-Time H-Res 2   | 0.5 lx, ~120 ms      |
| `0x23`  | One-Time L-Res     | 4 lx, ~16 ms         |


### Typical I²C Sequence
1. MCU sends Start + Device Address (0x23 or 0x5C)
2. Sends command (e.g. 0x10) to start measurement
3. Waits ~120 ms
4. Reads 2 bytes (MSB, LSB)
5. Combine into one 16-bit value
6. Convert to lux:

## License
MIT License — feel free to use, modify, and share.

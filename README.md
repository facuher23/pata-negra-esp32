# The Pata Negra ESP32

A high-performance ESP32-based line follower robot designed for speed, precision, and clean software architecture.

This project focuses not only on competitive performance but also on writing maintainable and modular C++ code using PlatformIO.

## Hardware

- **Microcontroller:** ESP32-S3 N16R8
- **Sensors:** TCRT 5000 * 5
- **Motor Driver:** TB6612FNG
- **Motors:** N20 1000 RPM 12V
- **Wheels:** Ø30 mm
- **Battery:** 2S 18650 Li-ion (7.4 V nominal)

## Software

- PlatformIO
- Arduino Framework
- C++

## Features

- PD controller
- Automatic sensor calibration
- PWM at 31.25 kHz
- Modular C++ architecture (.h/.cpp)

## Goals

- Fast and stable line tracking
- Clean and maintainable C++ code
- Easy hardware upgrades
- Reusable modules

## Future Improvements

- Integral term (PID)
- Bluetooth tuning
- Lap timing
- Telemetry

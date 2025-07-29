# Product Overview

This is an ESP-IDF template project that integrates Arduino as a component, designed for ESP32 microcontroller development. The project serves as a starting point for ESP32 applications that want to leverage both the power of ESP-IDF framework and the simplicity of Arduino functions.

## Key Features

- **Hybrid Framework**: Combines ESP-IDF's advanced capabilities with Arduino's ease of use
- **LED Blink Example**: Simple demonstration using built-in LED (GPIO2)
- **Ready-to-Use Template**: Pre-configured for immediate development
- **Kiro IDE Optimized**: Specifically configured for Kiro IDE workflow

## Target Hardware

- ESP32 family microcontrollers (ESP32, ESP32-S2, ESP32-S3, ESP32-C3, etc.)
- Compatible with any ESP32 development board
- Default LED pin: GPIO2 (configurable)

## Use Cases

- IoT device prototyping
- Learning ESP32 development
- Projects requiring both Arduino simplicity and ESP-IDF power
- Educational and hobbyist projects

## Quick Start

### Build the Project
```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py build
```

### Flash to ESP32
```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py -p COM5 flash
```

### Monitor Serial Output
```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py -p COM5 monitor
```

**Note**: Replace `COM5` with your actual serial port. Use `-b 115200` if you encounter flashing issues.
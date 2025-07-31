# Technology Stack & Commands

## Core Technologies

- **ESP-IDF**: v5.4.2+ (Espressif IoT Development Framework)
- **Arduino-ESP32**: v3.2.1+ (`espressif/arduino-esp32` component)
- **FreeRTOS**: 1000Hz tick rate (required for Arduino compatibility)
- **Build System**: CMake with ESP-IDF Component Manager
- **Language**: C++ with Arduino-style syntax
- **Platform**: Windows + PowerShell + Docker

## Development Environment

- **IDE**: Kiro IDE with ESP-IDF extension
- **ESP-IDF Path**: `%USERPROFILE%\esp\v5.4.2\esp-idf\`
- **Container**: `espressif/idf` Docker image
- **Entry Point**: `app_main()` with `extern "C"` linkage
- **Arduino Init**: `initArduino()` required before Arduino functions

## Commands

See `commands.md` for complete command reference and troubleshooting commands.
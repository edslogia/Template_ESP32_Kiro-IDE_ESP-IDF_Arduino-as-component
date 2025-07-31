# Technology Stack

## Build System
- **Primary**: ESP-IDF (Espressif IoT Development Framework) v5.4.2+
- **Build Tool**: CMake with ESP-IDF's project.cmake
- **Component Manager**: ESP-IDF Component Manager for dependency management
- **Target**: ESP32 family microcontrollers

## Frameworks & Libraries
- **ESP-IDF**: Core framework providing low-level hardware access and advanced features
- **Arduino-ESP32**: Arduino framework as a component (`espressif/arduino-esp32`)
- **FreeRTOS**: Real-time operating system (configured at 1000Hz tick rate)

## Development Environment
- **IDE**: Kiro IDE with ESP-IDF extension
- **ESP-IDF Version**: v5.4.2 (installed at `%USERPROFILE%\esp\v5.4.2\esp-idf\`)
- **Container**: Docker-based development environment using `espressif/idf` image
- **Language**: C++ (main.cpp uses Arduino-style syntax)
- **Platform**: Windows with PowerShell

## Key Configuration
- **FreeRTOS Tick Rate**: 1000Hz (required for Arduino compatibility)
- **Entry Point**: `app_main()` function with `extern "C"` linkage
- **Arduino Initialization**: `initArduino()` must be called before using Arduino functions

## Common Commands

Before running any ESP-IDF commands, the environment must be activated:
```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"
```
This script sets up:
- IDF_PATH environment variable
- Python dependencies
- Tool paths (compiler, flasher, etc.)

### Build & Flash
```powershell
# Build project (Windows - ESP-IDF environment setup required)
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py build

# Flash to device
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py flash

# Monitor serial output
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py monitor

# All-in-one command
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py build flash monitor
```

**Note**: The ESP-IDF environment must be activated before running any `idf.py` commands. The `export.ps1` script sets up the necessary environment variables and tool paths.

### Configuration
```bash
# Open configuration menu
idf.py menuconfig

# Set target device (run once per project)
idf.py set-target esp32
# or esp32s2, esp32s3, esp32c3, etc.
```

### Development Setup
```bash
# Generate compile_commands.json for code analysis
idf.py build
```
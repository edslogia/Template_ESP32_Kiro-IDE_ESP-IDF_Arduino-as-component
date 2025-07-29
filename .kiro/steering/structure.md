# Project Structure

## Root Directory Layout
```
├── main/                    # Main application component
│   ├── main.cpp            # Primary application code (Arduino-style C++)
│   ├── CMakeLists.txt      # Component build configuration
│   ├── CMakeLists.txt.example # Example CMakeLists configuration
│   └── idf_component.yml   # Component dependencies
├── managed_components/      # Auto-managed dependencies (26 components)
│   ├── espressif__arduino-esp32/    # Arduino ESP32 core v3.2.1
│   ├── espressif__esp-dsp/          # Digital Signal Processing
│   ├── espressif__esp-modbus/       # Modbus protocol support
│   ├── espressif__esp_rainmaker/    # ESP RainMaker IoT platform
│   ├── espressif__esp_insights/     # ESP Insights monitoring
│   ├── joltwallet__littlefs/        # LittleFS filesystem
│   └── ... (21 more components)     # Additional ESP-IDF components
├── build/                  # Build artifacts (generated, do not edit)
│   ├── bootloader/         # Bootloader build files
│   ├── esp-idf/           # Component build artifacts
│   ├── ESP32_PLC-in-DC_Kiro.bin   # Main application binary
│   ├── ESP32_PLC-in-DC_Kiro.elf   # ELF executable
│   ├── compile_commands.json       # Code analysis support
│   └── ... (build files)  # Other build artifacts
├── .devcontainer/          # Docker development environment
│   ├── devcontainer.json  # Container configuration
│   └── Dockerfile         # Container image definition
├── .kiro/                  # Kiro IDE configuration and steering
│   └── steering/          # Steering rules and documentation
│       ├── arduino-integration.md  # Arduino integration guide
│       ├── product.md     # Product overview
│       ├── structure.md   # This file - project structure
│       ├── tech.md        # Technology stack information
│       └── troubleshooting.md      # Common issues and solutions
├── .vscode/               # VS Code configuration (Kiro IDE)
│   ├── c_cpp_properties.json      # C/C++ IntelliSense config
│   ├── launch.json        # Debug configuration
│   └── settings.json      # IDE settings
├── .git/                  # Git version control
├── CMakeLists.txt         # Root project configuration
├── sdkconfig              # ESP-IDF configuration (auto-generated)
├── dependencies.lock      # Component manager lock file
├── .clangd                # Clang language server config
├── .gitignore            # Git ignore patterns
├── README.md             # Project documentation (Spanish)
└── README_EN.md          # Project documentation (English)
```

## Key Files & Directories

### Source Code
- **`main/main.cpp`**: Primary application entry point (LED blink example)
  - Contains `extern "C" void app_main()` function
  - Calls `initArduino()` before using Arduino functions
  - Uses Arduino-style GPIO functions (pinMode, digitalWrite, delay)
- **`main/CMakeLists.txt.example`**: Example component configuration

### Build Configuration
- **`CMakeLists.txt`**: Root project configuration, includes ESP-IDF project setup
- **`main/CMakeLists.txt`**: Component registration with Arduino dependency
- **`main/idf_component.yml`**: Declares Arduino-ESP32 and IDF dependencies

### Generated Files (Do Not Edit)
- **`sdkconfig`**: ESP-IDF configuration with FreeRTOS 1000Hz tick rate
- **`build/`**: All build artifacts and intermediate files
  - `ESP32_PLC-in-DC_Kiro.bin`: Main application binary (220KB)
  - `bootloader/bootloader.bin`: Bootloader binary (25KB)
  - `compile_commands.json`: Code analysis support for Kiro IDE
- **`managed_components/`**: 26 auto-downloaded components including Arduino ESP32
- **`dependencies.lock`**: Component manager dependency resolution

### Development Environment
- **`.devcontainer/`**: Docker configuration for consistent development environment
- **`.kiro/steering/`**: Kiro IDE steering rules and documentation
- **`.vscode/`**: Kiro IDE configuration files
- **`.git/`**: Git version control system

## Component Structure
This project follows ESP-IDF component architecture:
- Each directory with `CMakeLists.txt` is a component
- `main/` is the primary application component
- External components are managed via `idf_component.yml`

## Naming Conventions
- **Files**: Use lowercase with underscores (snake_case)
- **Directories**: Use lowercase with underscores
- **Functions**: Follow Arduino conventions (camelCase) or ESP-IDF conventions (snake_case)
- **GPIO References**: Use numeric pin numbers (e.g., GPIO2, not LED_BUILTIN)

## Adding New Components
1. Create new directory with `CMakeLists.txt`
2. Register component in root `CMakeLists.txt` if needed
3. Add dependencies in `idf_component.yml` if external libraries required

## Development Commands

All ESP-IDF commands require environment setup first:

### Build Project
```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py build
```

### Flash to Device
```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py -p COM5 flash
```

### Monitor Serial Output
```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py -p COM5 monitor
```

### Configuration Menu
```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py menuconfig
```

### Set Target Device
```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py set-target esp32
```

**Important**: Replace `COM5` with your actual serial port. Use `-b 115200` for slower but more reliable flashing.
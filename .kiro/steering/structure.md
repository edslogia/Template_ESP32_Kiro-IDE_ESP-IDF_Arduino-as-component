# Project Structure

## Root Directory Layout
```
├── main/                    # Main application component
│   ├── main.cpp            # Primary application code (Arduino-style C++)
│   ├── CMakeLists.txt      # Component build configuration
│   └── idf_component.yml   # Component dependencies
├── managed_components/      # Auto-managed dependencies (do not edit)
├── build/                  # Build artifacts (generated, gitignored)
├── .devcontainer/          # Docker development environment
├── .kiro/                  # Kiro IDE configuration and steering
├── CMakeLists.txt          # Root project configuration
├── sdkconfig               # ESP-IDF configuration (auto-generated)
├── dependencies.lock       # Component manager lock file
└── README.md              # Project documentation
```

## Key Files & Directories

### Source Code
- **`main/main.cpp`**: Primary application entry point
  - Must contain `extern "C" void app_main()` function
  - Call `initArduino()` before using Arduino functions
  - Use Arduino-style GPIO functions (pinMode, digitalWrite, etc.)

### Build Configuration
- **`CMakeLists.txt`**: Root project configuration, includes ESP-IDF project setup
- **`main/CMakeLists.txt`**: Component registration for main application
- **`main/idf_component.yml`**: Declares Arduino-ESP32 dependency

### Generated Files (Do Not Edit)
- **`sdkconfig`**: ESP-IDF configuration, auto-generated from menuconfig
- **`build/`**: All build artifacts and intermediate files
- **`managed_components/`**: Component manager downloads
- **`dependencies.lock`**: Dependency resolution cache

### Development Environment
- **`.devcontainer/`**: Docker configuration for consistent development environment
- **`.kiro/`**: Kiro IDE settings and steering rules

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
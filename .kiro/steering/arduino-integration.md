# Arduino Integration with ESP-IDF

## Overview
This project uses Arduino as an ESP-IDF component, providing the full flexibility of ESP-IDF with the simplicity of Arduino functions. The Arduino component is managed via IDF Component Manager.

## Version Compatibility
- **Arduino Core ESP32**: v3.2.1+
- **ESP-IDF**: v5.4+
- **Component**: `espressif/arduino-esp32`

## Two Implementation Approaches

### Option 1: Arduino-style (setup/loop)
Traditional Arduino approach with automatic startup:

```cpp
#include "Arduino.h"

void setup() {
    Serial.begin(115200);
    pinMode(2, OUTPUT);
}

void loop() {
    digitalWrite(2, HIGH);
    delay(500);
    digitalWrite(2, LOW);
    delay(500);
}
```

**Configuration**: Enable "Autostart Arduino setup and loop on boot" in menuconfig

### Option 2: ESP-IDF style (app_main) - CURRENT PROJECT
Manual Arduino initialization with full ESP-IDF control:

```cpp
#include "Arduino.h"

extern "C" void app_main() {
    initArduino();  // Required before using Arduino functions
    
    // Your Arduino-style code here
    pinMode(2, OUTPUT);
    while(true) {
        digitalWrite(2, HIGH);
        delay(500);
        digitalWrite(2, LOW);
        delay(500);
    }
    // WARNING: Function must not end or MCU will restart
}
```

**Configuration**: Disable "Autostart Arduino setup and loop on boot" in menuconfig

## Critical Requirements

### FreeRTOS Configuration
- **Tick Rate**: Must be 1000Hz (`CONFIG_FREERTOS_HZ=1000`)
- **Location**: Component config → FreeRTOS → Tick rate
- **Why**: Arduino timing functions require 1ms precision

### File Extensions
- Use `.cpp` for files with Arduino functions
- Update `CMakeLists.txt` to reference `.cpp` files
- Arduino libraries require C++ compilation

## Adding Arduino Libraries

### Method 1: Global Libraries (Recommended)
Add to the Arduino component itself:

```bash
cd components/arduino-esp32/libraries
git clone --recursive https://github.com/Author/LibraryName.git
```

Then update `components/arduino-esp32/CMakeLists.txt`:
- Add source files to `LIBRARY_SRCS`
- Add include paths to `includedirs`

### Method 2: Local Project Libraries
Create as separate ESP-IDF component:

```bash
mkdir -p components/my_library
cd components/my_library
```

Create `CMakeLists.txt`:
```cmake
idf_component_register(
    SRCS "library_source.cpp"
    INCLUDE_DIRS "."
    REQUIRES arduino-esp32
)
```

### Method 3: IDF Component Manager
Add to `main/idf_component.yml`:
```yaml
dependencies:
  espressif/arduino-esp32: '*'
  your_namespace/your_library: '^1.0.0'
```

## Configuration Menu Options

Access via `idf.py menuconfig → Arduino Configuration`:

- **Autostart Arduino**: Enable/disable automatic setup/loop
- **Core Debug Level**: Set Arduino logging level
- **Event Task**: Configure Arduino event handling
- **Serial configurations**: UART settings for Serial object

## Logging Integration

### Arduino Serial with ESP-IDF Logging
```cpp
#ifdef ARDUINO_ARCH_ESP32
#include "esp32-hal-log.h"
#endif

// Use ESP_LOGx macros alongside Serial.print
ESP_LOGI("TAG", "This works in Arduino IDE too");
Serial.println("Traditional Arduino logging");
```

## Common Issues & Solutions

### Compilation Errors
- Ensure file extensions are `.cpp` for Arduino code
- Check ESP-IDF and Arduino component version compatibility
- Verify FreeRTOS tick rate is 1000Hz

### Missing Functions
- Call `initArduino()` before using Arduino functions in `app_main()`
- Include `"Arduino.h"` in files using Arduino functions
- Ensure component dependencies are declared in `CMakeLists.txt`

### USB HID Classes (ESP32-S2/S3)
For USBHID classes, additional setup required:
```bash
git clone https://github.com/espressif/esp32-arduino-lib-builder.git
git clone https://github.com/hathach/tinyusb.git esp32-arduino-lib-builder/components/arduino_tinyusb/tinyusb
```

Add to root `CMakeLists.txt` before `project()`:
```cmake
set(EXTRA_COMPONENT_DIRS path/to/esp32-arduino-lib-builder/components/arduino_tinyusb)
```

## Best Practices

1. **Always call `initArduino()`** before Arduino functions in `app_main()`
2. **Use infinite loops** in `app_main()` to prevent MCU restart
3. **Declare Arduino dependency** in component `CMakeLists.txt`
4. **Check version compatibility** when updating components
5. **Use `.cpp` extensions** for Arduino-compatible code
6. **Configure FreeRTOS tick rate** to 1000Hz for timing accuracy
# ESP-IDF with Arduino Template for Kiro

This is a base template for ESP-IDF projects that uses Arduino as a component, optimized for working with Kiro IDE.

## Features

- **ESP-IDF Framework**: Uses Espressif's official framework
- **Arduino as Component**: Allows using familiar Arduino functions (digitalWrite, pinMode, delay, etc.)
- **Ready Configuration**: Pre-configured project ready to use
- **Built-in LED**: Basic example that blinks the built-in LED (GPIO2)

## Project Structure

```
├── main/
│   ├── main.cpp          # Main application code
│   └── CMakeLists.txt    # Build configuration for main
├── CMakeLists.txt        # Main project configuration
├── sdkconfig             # SDK configuration (auto-generated)
└── README.md            # This file
```

## Prerequisites

1. **ESP-IDF**: Version 4.4 or higher
2. **ESP-IDF Extension**: Installed in Kiro IDE
3. **Hardware**: Any compatible ESP32 board

## Initial Setup

### 1. Configure ESP-IDF in Kiro

1. Open command palette (`Ctrl+Shift+P`)
2. Search for "ESP-IDF: Configure ESP-IDF Extension"
3. Follow instructions to configure your ESP-IDF installation

### 2. Select Target

1. Open command palette
2. Run "ESP-IDF: Set Espressif Device Target"
3. Select your ESP32 model (esp32, esp32s2, esp32s3, esp32c3, etc.)

## Usage

### Build Project

```bash
idf.py build
```

Or use Kiro command: `ESP-IDF: Build Project`

### Flash to Board

```bash
idf.py flash
```

Or use Kiro command: `ESP-IDF: Flash Device`

### Serial Monitor

```bash
idf.py monitor
```

Or use Kiro command: `ESP-IDF: Monitor Device`

### All in One

```bash
idf.py build flash monitor
```

## Example Code

The project includes a basic example that blinks the built-in LED:

```cpp
#include "Arduino.h"

extern "C" void app_main()
{
    initArduino();
    pinMode(2, OUTPUT);  // GPIO2 is the built-in LED
    
    while(true) {
        digitalWrite(2, HIGH);  // Turn LED on
        delay(500);             // Wait 500ms
        digitalWrite(2, LOW);   // Turn LED off
        delay(500);             // Wait 500ms
    }
}
```

## Customization

### Change LED Pin

If your board uses a different GPIO for the built-in LED, modify the number in `main.cpp`:

```cpp
pinMode(YOUR_GPIO_HERE, OUTPUT);
digitalWrite(YOUR_GPIO_HERE, HIGH);
digitalWrite(YOUR_GPIO_HERE, LOW);
```

### Add More Functionality

You can use all the usual Arduino functions:
- `analogRead()`, `analogWrite()`
- `Serial.begin()`, `Serial.print()`
- `WiFi.begin()`, `WiFi.connect()`
- And many more...

## Advanced Configuration

### Modify SDK Configuration

```bash
idf.py menuconfig
```

This opens a configuration menu where you can:
- Adjust WiFi settings
- Modify memory configurations
- Enable/disable components
- And much more

### Add Additional Components

To add ESP-IDF components, modify the `main/CMakeLists.txt` file:

```cmake
idf_component_register(SRCS "main.cpp"
                       INCLUDE_DIRS "."
                       REQUIRES arduino-esp32 your_component_here)
```

## Troubleshooting

### Build Error
- Verify ESP-IDF is correctly installed
- Make sure you've selected the correct target
- Check that all dependencies are installed

### Flash Error
- Verify the board is connected correctly
- Make sure the serial port is correct
- Try pressing the BOOT button while flashing

### LED Not Blinking
- Verify you're using the correct GPIO for your board
- Some ESP32 use GPIO2, others GPIO8 or GPIO10
- Check your specific board documentation

## Useful Resources

- [ESP-IDF Documentation](https://docs.espressif.com/projects/esp-idf/)
- [Arduino-ESP32 GitHub](https://github.com/espressif/arduino-esp32)
- [ESP32 Guides](https://randomnerdtutorials.com/getting-started-with-esp32/)

## Contributing

If you find improvements for this template, feel free to suggest changes or create a fork of the project.

## License

This project is in the public domain. Use it freely for your projects.
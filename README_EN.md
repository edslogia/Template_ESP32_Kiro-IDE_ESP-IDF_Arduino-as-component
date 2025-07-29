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

1. **ESP-IDF**: Version 5.4.2 installed at `%USERPROFILE%\esp\v5.4.2\esp-idf\`
2. **ESP-IDF Extension**: Installed in Kiro IDE
3. **Hardware**: Any compatible ESP32 board
4. **Operating System**: Windows with PowerShell

## Initial Setup

### 1. Configure ESP-IDF in Kiro

1. Open command palette (`Ctrl+Shift+P`)
2. Search for "ESP-IDF: Configure ESP-IDF Extension"
3. Follow instructions to configure your ESP-IDF installation

### 2. Generate compile_commands.json (Required for Kiro)

When opening the project for the first time, Kiro will show the message:

```
compile_commands.json is missing. This may cause errors with code analysis extensions.
```

**Solution:** Click "Generate compile_commands.json" or run:

```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py build
```

This will generate the file needed for code analysis.

### 3. Select Target

1. Open command palette
2. Run "ESP-IDF: Set Espressif Device Target"
3. Select your ESP32 model (esp32, esp32s2, esp32s3, esp32c3, etc.)

## Usage

### Build Project

```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py build
```

Or use Kiro command: `ESP-IDF: Build Project`

**⚠️ Important:** If you get a Python environment error like:

```
'python.exe' is currently active while the project was configured with different version
Run 'idf.py fullclean' to start again
```

**Solution:** Run a full clean first:

```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py fullclean
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py build
```

### Identify Serial Port

Before flashing, identify the correct port for your ESP32:

```powershell
Get-PnpDevice -Class Ports -Status OK | Select-Object FriendlyName, InstanceId
```

Look for devices like:

- `Silicon Labs CP210x USB to UART Bridge (COM5)`
- `USB-SERIAL CH340 (COM3)`
- `USB Serial Port (COM4)`

### Flash to Board

```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py -p COM5 flash
```

**Note:** Replace `COM5` with your detected serial port.

**⚠️ If flashing fails with boot mode error:**

1. **First attempt:** Use slower speed:

   ```powershell
   & "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py -p COM5 -b 115200 flash
   ```

2. **If problem persists:** Use esptool directly:

   ```powershell
   & "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; python -m esptool --chip esp32 -p COM5 -b 115200 --before default_reset --after hard_reset write_flash --flash_mode dio --flash_freq 40m --flash_size 2MB 0x1000 build\bootloader\bootloader.bin 0x8000 build\partition_table\partition-table.bin 0x10000 build\ESP32_PLC-in-DC_Kiro.bin
   ```

3. **Manual method:** Hold the BOOT button on the board while running the flash command.

Or use Kiro command: `ESP-IDF: Flash Device`

### Serial Monitor

```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py -p COM5 monitor
```

Or use Kiro command: `ESP-IDF: Monitor Device`

### All in One

```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py -p COM5 build flash monitor
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

```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py menuconfig
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

### Arduino Dependency Error (ALREADY FIXED)

If you get build errors related to Arduino functions not found, verify that the `main/CMakeLists.txt` file contains:

```cmake
idf_component_register(
    SRCS "main.cpp"
    INCLUDE_DIRS ""
    REQUIRES arduino-esp32  # CRITICAL: Required for Arduino functions
)
```

**Note:** This template already includes the correct configuration. If you modify the file, make sure to keep the `REQUIRES arduino-esp32` line.

### FreeRTOS Error (ALREADY FIXED)

If you get the error:

```
esp32-arduino requires CONFIG_FREERTOS_HZ=1000 (currently 100)
```

**Note:** This template already has the correct configuration (`CONFIG_FREERTOS_HZ=1000`) in the `sdkconfig` file. If you still see this error, verify that the `sdkconfig` file is present and contains the correct line.

### Python Environment Error

If you get an error like:

```
'python.exe' is currently active while the project was configured with different version
Run 'idf.py fullclean' to start again
```

**Solution:** This is a common error when the ESP-IDF Python environment changes. Run:

```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py fullclean
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py build
```

### Build Error

- Verify ESP-IDF is correctly installed
- Make sure you've selected the correct target
- Check that all dependencies are installed
- If you get Python environment errors, use the solution above

### Flash Error

#### Error: "Wrong boot mode detected (0x13)"

```
A fatal error occurred: Failed to connect to ESP32: Wrong boot mode detected (0x13)!
The chip needs to be in download mode.
```

**Solutions in order of priority:**

1. **Use slower speed:**

   ```powershell
   & "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py -p COM5 -b 115200 flash
   ```

2. **Use esptool directly:**

   ```powershell
   & "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; python -m esptool --chip esp32 -p COM5 -b 115200 --before default_reset --after hard_reset write_flash --flash_mode dio --flash_freq 40m --flash_size 2MB 0x1000 build\bootloader\bootloader.bin 0x8000 build\partition_table\partition-table.bin 0x10000 build\ESP32_PLC-in-DC_Kiro.bin
   ```

3. **Manual method:** Hold the BOOT button while running the flash command.

#### Error: "The chip stopped responding"

If the chip connects but stops during flash configuration:

- Use esptool directly (command from point 2 above)
- Check USB cable quality (must support data, not just charging)
- Try a different USB cable

#### Error: "Could not open COM port"

- Verify the board is connected correctly
- Make sure the serial port is correct using: `Get-PnpDevice -Class Ports -Status OK`
- Close other programs that might be using the port (Arduino IDE, PuTTY, etc.)
- Disconnect and reconnect the USB cable

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

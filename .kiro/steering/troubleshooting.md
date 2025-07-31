# Common Troubleshooting - ESP-IDF + Arduino

## Compilation Errors

### 1. Error: Arduino functions not found

**Symptoms:**

```
undefined reference to `pinMode'
undefined reference to `digitalWrite'
undefined reference to `initArduino'
```

**Cause:** Missing Arduino dependency in CMakeLists.txt

**Solution:**
Verify that `main/CMakeLists.txt` contains:

```cmake
idf_component_register(
    SRCS "main.cpp"
    INCLUDE_DIRS ""
    REQUIRES arduino-esp32  # CRÍTICO
)
```

### 2. Error: managed_components hash mismatch

**Symptoms:**

```
ERROR: Some components in the "managed_components" directory were modified
Hash of the file "CMakeLists.txt" does not match expected hash
```

**Solution:**

```powershell
Remove-Item -Recurse -Force managed_components
Remove-Item -Recurse -Force build
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py build
```

### 3. Error: Python environment mismatch

**Symptoms:**

```
'python.exe' is currently active while the project was configured with different version
Run 'idf.py fullclean' to start again
```

**Solution:**

```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py fullclean
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py build
```

**Note:** This is a common error that occurs when the ESP-IDF Python environment version changes. A full clean resolves the issue by regenerating all configuration files.

## Configuration Errors

### 4. Error: FreeRTOS tick rate

**Symptoms:**

```
esp32-arduino requires CONFIG_FREERTOS_HZ=1000 (currently 100)
```

**Solution:**
Verify that `sdkconfig` contains:

```
CONFIG_FREERTOS_HZ=1000
```

If it doesn't exist, run:

```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py menuconfig
```

Navigate to: Component config → FreeRTOS → Tick rate (Hz) → 1000

## Flash Errors

### 5. Error: Failed to connect to ESP32

**Symptoms:**

```
Failed to connect to ESP32: Timed out waiting for packet header
```

Or:

```
A fatal error occurred: Failed to connect to ESP32: Wrong boot mode detected (0x13)!
The chip needs to be in download mode.
```

**Solutions in order of priority:**

1. **Identify correct port:**

   ```powershell
   Get-PnpDevice -Class Ports -Status OK | Select-Object FriendlyName, InstanceId
   ```

   Look for: `Silicon Labs CP210x USB to UART Bridge (COM5)`

2. **Use slower speed:**

   ```powershell
   & "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py -p COM5 -b 115200 flash
   ```

3. **Use esptool directly (MORE RELIABLE):**

   ```powershell
   & "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; python -m esptool --chip esp32 -p COM5 -b 115200 --before default_reset --after hard_reset write_flash --flash_mode dio --flash_freq 40m --flash_size 2MB 0x1000 build\bootloader\bootloader.bin 0x8000 build\partition_table\partition-table.bin 0x10000 build\ESP32_PLC-in-DC_Kiro.bin
   ```

4. **Manual method:** Press BOOT button while flashing
5. **Check USB cable** (must support data, not just charging)

### 6. Error: Permission denied on COM port

**Symptoms:**

```
could not open port 'COM5': PermissionError
```

Or:

```
could not open port '\\\\.\\COM5': PermissionError(13, 'Access denied.', None, 5)
```

**Solutions:**

1. Close other programs using the port (Arduino IDE, PuTTY, etc.)
2. Disconnect and reconnect the USB cable
3. Check device drivers
4. Wait a few seconds after flashing before opening the monitor
5. Restart Kiro IDE if the problem persists

### 7. Error: The chip stopped responding

**Symptoms:**

```
A fatal error occurred: The chip stopped responding.
```

**Cause:** Communication problem during flash configuration with `idf.py flash`

**Solution:** Use esptool directly (more stable):

```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; python -m esptool --chip esp32 -p COM5 -b 115200 --before default_reset --after hard_reset write_flash --flash_mode dio --flash_freq 40m --flash_size 2MB 0x1000 build\bootloader\bootloader.bin 0x8000 build\partition_table\partition-table.bin 0x10000 build\ESP32_PLC-in-DC_Kiro.bin
```

## Kiro IDE Errors

### 8. Error: compile_commands.json missing

**Symptoms:**

```
compile_commands.json is missing. This may cause errors with code analysis
```

**Solution:**

```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py build
```

### 9. Error: IntelliSense not working

**Symptoms:**

- Arduino functions appear as undefined
- Autocompletion doesn't work

**Solutions:**

1. Generate compile_commands.json (see error #8)
2. Restart Kiro IDE
3. Check ESP-IDF extension configuration

## Recommended Workflow

### Build and Flash Process (Tested)

1. **Identify ESP32 port:**

   ```powershell
   Get-PnpDevice -Class Ports -Status OK | Select-Object FriendlyName, InstanceId
   ```

2. **Build project:**

   ```powershell
   & "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py build
   ```

   If there's a Python environment error, clean first:

   ```powershell
   & "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py fullclean
   & "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py build
   ```

3. **Flash (most reliable method):**

   ```powershell
   & "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; python -m esptool --chip esp32 -p COM5 -b 115200 --before default_reset --after hard_reset write_flash --flash_mode dio --flash_freq 40m --flash_size 2MB 0x1000 build\bootloader\bootloader.bin 0x8000 build\partition_table\partition-table.bin 0x10000 build\ESP32_PLC-in-DC_Kiro.bin
   ```

4. **Serial monitor (optional):**
   ```powershell
   & "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py -p COM5 monitor
   ```

**Note:** Replace `COM5` with the port detected in step 1.

## Problem Prevention

### Files that should NOT be modified:

- `managed_components/` (auto-regenerated)
- `build/` (build files)
- `sdkconfig.old` (automatic backup)

### Critical files:

- `main/CMakeLists.txt` - MUST include `REQUIRES arduino-esp32`
- `main/idf_component.yml` - MUST include `espressif/arduino-esp32: '*'`
- `sdkconfig` - MUST have `CONFIG_FREERTOS_HZ=1000`

### Safe cleanup commands:

```powershell
# Full build clean
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py fullclean

# Clean only managed components
Remove-Item -Recurse -Force managed_components
Remove-Item -Recurse -Force build
```

### Recommended .gitignore:

```gitignore
# Build artifacts
build/
sdkconfig.old

# Managed components (auto-downloaded)
managed_components/

# IDE files
.vscode/settings.json
.vscode/c_cpp_properties.json
compile_commands.json
```

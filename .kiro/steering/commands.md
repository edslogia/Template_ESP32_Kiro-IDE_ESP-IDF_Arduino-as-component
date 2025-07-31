# Command Reference

Quick reference for common ESP-IDF + Arduino development commands.

## Environment Setup (Always Required First)

```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"
```

This sets up:
- IDF_PATH environment variable
- Python dependencies  
- Tool paths (compiler, flasher, etc.)

## Port Detection

```powershell
Get-PnpDevice -Class Ports -Status OK | Select-Object FriendlyName, InstanceId
```
Look for: `Silicon Labs CP210x USB to UART Bridge (COM5)`

## Standard Workflow

### Build
```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py build
```

### Flash (replace COM5 with your port)
```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py -p COM5 flash
```

### Monitor
```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py -p COM5 monitor
```

### All-in-one
```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py -p COM5 build flash monitor
```

## Configuration

### Open menuconfig
```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py menuconfig
```

### Set target device (run once per project)
```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py set-target esp32
```

## Troubleshooting Commands

### Clean build (Python environment issues)
```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py fullclean
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py build
```

### Clean managed components (hash mismatch)
```powershell
Remove-Item -Recurse -Force managed_components
Remove-Item -Recurse -Force build
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py build
```

### Flash with slower speed (connection issues)
```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py -p COM5 -b 115200 flash
```

### Direct esptool flash (most reliable)
```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; python -m esptool --chip esp32 -p COM5 -b 115200 --before default_reset --after hard_reset write_flash --flash_mode dio --flash_freq 40m --flash_size 2MB 0x1000 build\bootloader\bootloader.bin 0x8000 build\partition_table\partition-table.bin 0x10000 build\ESP32_PLC-in-DC_Kiro.bin
```

## Notes

- Replace `COM5` with your actual serial port
- Use `-b 115200` for slower baud rate if flashing fails
- Always activate ESP-IDF environment before running commands
- See `troubleshooting.md` for detailed error solutions
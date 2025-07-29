# Solución de Problemas Comunes - ESP-IDF + Arduino

## Errores de Compilación

### 1. Error: Arduino functions not found

**Síntomas:**
```
undefined reference to `pinMode'
undefined reference to `digitalWrite'
undefined reference to `initArduino'
```

**Causa:** Falta la dependencia de Arduino en CMakeLists.txt

**Solución:**
Verificar que `main/CMakeLists.txt` contenga:
```cmake
idf_component_register(
    SRCS "main.cpp"
    INCLUDE_DIRS ""
    REQUIRES arduino-esp32  # CRÍTICO
)
```

### 2. Error: managed_components hash mismatch

**Síntomas:**
```
ERROR: Some components in the "managed_components" directory were modified
Hash of the file "CMakeLists.txt" does not match expected hash
```

**Solución:**
```powershell
Remove-Item -Recurse -Force managed_components
Remove-Item -Recurse -Force build
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py build
```

### 3. Error: Python environment mismatch

**Síntomas:**
```
'python.exe' is currently active while the project was configured with different version
Run 'idf.py fullclean' to start again
```

**Solución:**
```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py fullclean
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py build
```

**Nota:** Este es un error común que ocurre cuando se cambia la versión de Python del entorno ESP-IDF. La limpieza completa resuelve el problema regenerando todos los archivos de configuración.

## Errores de Configuración

### 4. Error: FreeRTOS tick rate

**Síntomas:**
```
esp32-arduino requires CONFIG_FREERTOS_HZ=1000 (currently 100)
```

**Solución:**
Verificar que `sdkconfig` contenga:
```
CONFIG_FREERTOS_HZ=1000
```

Si no existe, ejecutar:
```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py menuconfig
```
Navegar a: Component config → FreeRTOS → Tick rate (Hz) → 1000

## Errores de Flash

### 5. Error: Failed to connect to ESP32

**Síntomas:**
```
Failed to connect to ESP32: Timed out waiting for packet header
```
O:
```
A fatal error occurred: Failed to connect to ESP32: Wrong boot mode detected (0x13)!
The chip needs to be in download mode.
```

**Soluciones en orden de prioridad:**
1. **Identificar puerto correcto:**
   ```powershell
   Get-PnpDevice -Class Ports -Status OK | Select-Object FriendlyName, InstanceId
   ```
   Buscar: `Silicon Labs CP210x USB to UART Bridge (COM5)`

2. **Usar velocidad más lenta:**
   ```powershell
   & "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py -p COM5 -b 115200 flash
   ```

3. **Usar esptool directamente (MÁS CONFIABLE):**
   ```powershell
   & "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; python -m esptool --chip esp32 -p COM5 -b 115200 --before default_reset --after hard_reset write_flash --flash_mode dio --flash_freq 40m --flash_size 2MB 0x1000 build\bootloader\bootloader.bin 0x8000 build\partition_table\partition-table.bin 0x10000 build\ESP32_PLC-in-DC_Kiro.bin
   ```

4. **Método manual:** Presionar botón BOOT mientras flashea
5. **Verificar cable USB** (debe soportar datos, no solo carga)

### 6. Error: Permission denied on COM port

**Síntomas:**
```
could not open port 'COM5': PermissionError
```
O:
```
could not open port '\\\\.\\COM5': PermissionError(13, 'Acceso denegado.', None, 5)
```

**Soluciones:**
1. Cerrar otros programas que usen el puerto (Arduino IDE, PuTTY, etc.)
2. Desconectar y reconectar el cable USB
3. Verificar drivers del dispositivo
4. Esperar unos segundos después del flasheo antes de abrir el monitor
5. Reiniciar Kiro IDE si el problema persiste

### 7. Error: The chip stopped responding

**Síntomas:**
```
A fatal error occurred: The chip stopped responding.
```

**Causa:** Problema de comunicación durante la configuración del flash con `idf.py flash`

**Solución:** Usar esptool directamente (más estable):
```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; python -m esptool --chip esp32 -p COM5 -b 115200 --before default_reset --after hard_reset write_flash --flash_mode dio --flash_freq 40m --flash_size 2MB 0x1000 build\bootloader\bootloader.bin 0x8000 build\partition_table\partition-table.bin 0x10000 build\ESP32_PLC-in-DC_Kiro.bin
```

## Errores de Kiro IDE

### 8. Error: compile_commands.json missing

**Síntomas:**
```
compile_commands.json is missing. This may cause errors with code analysis
```

**Solución:**
```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py build
```

### 9. Error: IntelliSense not working

**Síntomas:**
- Funciones Arduino aparecen como no definidas
- Autocompletado no funciona

**Soluciones:**
1. Generar compile_commands.json (ver error #7)
2. Reiniciar Kiro IDE
3. Verificar configuración ESP-IDF extension

## Flujo de Trabajo Recomendado

### Proceso de Compilación y Flasheo (Probado)

1. **Identificar puerto ESP32:**
   ```powershell
   Get-PnpDevice -Class Ports -Status OK | Select-Object FriendlyName, InstanceId
   ```

2. **Compilar proyecto:**
   ```powershell
   & "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py build
   ```
   
   Si hay error de entorno Python, limpiar primero:
   ```powershell
   & "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py fullclean
   & "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py build
   ```

3. **Flashear (método más confiable):**
   ```powershell
   & "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; python -m esptool --chip esp32 -p COM5 -b 115200 --before default_reset --after hard_reset write_flash --flash_mode dio --flash_freq 40m --flash_size 2MB 0x1000 build\bootloader\bootloader.bin 0x8000 build\partition_table\partition-table.bin 0x10000 build\ESP32_PLC-in-DC_Kiro.bin
   ```

4. **Monitor serial (opcional):**
   ```powershell
   & "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py -p COM5 monitor
   ```

**Nota:** Reemplazar `COM5` con el puerto detectado en el paso 1.

## Prevención de Problemas

### Archivos que NO deben modificarse:
- `managed_components/` (se regenera automáticamente)
- `build/` (archivos de compilación)
- `sdkconfig.old` (backup automático)

### Archivos críticos:
- `main/CMakeLists.txt` - DEBE incluir `REQUIRES arduino-esp32`
- `main/idf_component.yml` - DEBE incluir `espressif/arduino-esp32: '*'`
- `sdkconfig` - DEBE tener `CONFIG_FREERTOS_HZ=1000`

### Comandos de limpieza seguros:
```powershell
# Limpiar build completo
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py fullclean

# Limpiar solo componentes gestionados
Remove-Item -Recurse -Force managed_components
Remove-Item -Recurse -Force build
```

### .gitignore recomendado:
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
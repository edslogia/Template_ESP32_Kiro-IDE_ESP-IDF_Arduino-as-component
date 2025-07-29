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

**Soluciones:**
1. Verificar puerto COM correcto
2. Presionar botón BOOT mientras flashea
3. Usar velocidad más lenta: `-b 115200`
4. Verificar cable USB (debe soportar datos, no solo carga)

### 6. Error: Permission denied on COM port

**Síntomas:**
```
could not open port 'COM5': PermissionError
```

**Soluciones:**
1. Cerrar otros programas que usen el puerto (Arduino IDE, PuTTY, etc.)
2. Desconectar y reconectar el cable USB
3. Verificar drivers del dispositivo

## Errores de Kiro IDE

### 7. Error: compile_commands.json missing

**Síntomas:**
```
compile_commands.json is missing. This may cause errors with code analysis
```

**Solución:**
```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py build
```

### 8. Error: IntelliSense not working

**Síntomas:**
- Funciones Arduino aparecen como no definidas
- Autocompletado no funciona

**Soluciones:**
1. Generar compile_commands.json (ver error #7)
2. Reiniciar Kiro IDE
3. Verificar configuración ESP-IDF extension

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
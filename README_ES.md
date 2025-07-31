# ESP-IDF con Arduino Template para Kiro

Esta es una plantilla base para proyectos ESP-IDF que utiliza Arduino como componente, optimizada para trabajar con Kiro IDE.

## 🚀 Ventajas Principales

### ✨ Personalización Inteligente
- **Personalización con IA**: Kiro se adapta automáticamente a tu nivel de experiencia y preferencias
- **Flexibilidad de Idioma**: Elige entre comentarios y explicaciones en español, inglés o mixto
- **Aprendizaje Adaptativo**: Mientras más lo uses, mejor entiende tu estilo de programación
- **Asistencia por Nivel**: Orientación diferente para principiantes, intermedios y desarrolladores avanzados

### ⚡ Configuración Cero
- **Entorno Preconfigurado**: Toda la integración ESP-IDF + Arduino lista para usar desde el primer momento
- **Gestión de Dependencias**: 26+ componentes gestionados y configurados automáticamente
- **Sistema de Compilación Listo**: Configuración CMake con dependencias Arduino incluidas
- **FreeRTOS Optimizado**: Tick rate preconfigurado a 1000Hz para compatibilidad con Arduino
- **Soporte Docker**: Entorno de desarrollo consistente en diferentes máquinas

### 🎯 Integración con Kiro IDE
- **Análisis Inteligente de Código**: Generación preconfigurada de compile_commands.json
- **Asistencia Contextual**: Reglas de steering integradas para mejores prácticas de desarrollo ESP32
- **Guías de Solución**: Soluciones completas de errores y referencias de comandos
- **Comandos de Un Clic**: Compilar, flashear y monitorear con comandos integrados del IDE

## Características

- **ESP-IDF Framework**: Utiliza el framework oficial de Espressif
- **Arduino como Componente**: Permite usar las funciones familiares de Arduino (digitalWrite, pinMode, delay, etc.)
- **Configuración Lista**: Proyecto preconfigurado y listo para usar
- **LED Integrado**: Ejemplo básico que hace parpadear el LED integrado (GPIO2)

## Estructura del Proyecto

```
├── main/                    # Componente principal de la aplicación
│   ├── main.cpp            # Código principal (ejemplo LED parpadeante)
│   ├── CMakeLists.txt      # Configuración de compilación con dependencia Arduino
│   ├── CMakeLists.txt.example # Ejemplo de configuración
│   └── idf_component.yml   # Dependencias del componente
├── managed_components/      # Componentes gestionados automáticamente (26 total)
│   ├── espressif__arduino-esp32/    # Arduino ESP32 core v3.2.1
│   ├── espressif__esp-dsp/          # Procesamiento de señales digitales
│   ├── espressif__esp-modbus/       # Soporte protocolo Modbus
│   ├── espressif__esp_rainmaker/    # Plataforma IoT ESP RainMaker
│   └── ... (22 componentes más)     # Componentes adicionales ESP-IDF
├── build/                  # Artefactos de compilación (generados automáticamente)
│   ├── ESP32_PLC-in-DC_Kiro.bin   # Binario principal de la aplicación
│   ├── bootloader/bootloader.bin   # Binario del bootloader
│   └── compile_commands.json       # Soporte para análisis de código
├── .devcontainer/          # Entorno de desarrollo Docker
├── .kiro/                  # Configuración y reglas de Kiro IDE
│   └── steering/          # Documentación y guías del proyecto
├── .vscode/               # Configuración de Kiro IDE
├── CMakeLists.txt         # Configuración principal del proyecto
├── sdkconfig              # Configuración ESP-IDF (FreeRTOS 1000Hz)
├── dependencies.lock      # Bloqueo de dependencias del gestor de componentes
├── README.md             # Este archivo (Español)
└── README_EN.md          # Documentación en Inglés
```

## Requisitos Previos

1. **ESP-IDF**: Versión 5.4.2 instalada en `%USERPROFILE%\esp\v5.4.2\esp-idf\`
2. **Extensión ESP-IDF**: Instalada en Kiro IDE
3. **Hardware**: Cualquier placa ESP32 compatible
4. **Sistema Operativo**: Windows con PowerShell

## Configuración Inicial

### 1. Configurar ESP-IDF en Kiro

1. Abre la paleta de comandos (`Ctrl+Shift+P`)
2. Busca "ESP-IDF: Configure ESP-IDF Extension"
3. Sigue las instrucciones para configurar tu instalación de ESP-IDF

### 2. Generar compile_commands.json (Requerido para Kiro)

Al abrir el proyecto por primera vez, Kiro mostrará el mensaje:

```
compile_commands.json is missing. This may cause errors with code analysis extensions.
```

**Solución:** Haz clic en "Generate compile_commands.json" o ejecuta:

```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py build
```

Esto generará el archivo necesario para el análisis de código.

### 3. Seleccionar Target

1. Abre la paleta de comandos
2. Ejecuta "ESP-IDF: Set Espressif Device Target"
3. Selecciona tu modelo de ESP32 (esp32, esp32s2, esp32s3, esp32c3, etc.)

## Uso

### Compilar el Proyecto

```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py build
```

O usa el comando de Kiro: `ESP-IDF: Build Project`

**⚠️ Importante:** Si obtienes un error de entorno Python como:
```
'python.exe' is currently active while the project was configured with different version
Run 'idf.py fullclean' to start again
```

**Solución:** Ejecuta primero una limpieza completa:
```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py fullclean
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py build
```

### Identificar Puerto Serial

Antes de flashear, identifica el puerto correcto de tu ESP32:

```powershell
Get-PnpDevice -Class Ports -Status OK | Select-Object FriendlyName, InstanceId
```

Busca dispositivos como:
- `Silicon Labs CP210x USB to UART Bridge (COM5)`
- `USB-SERIAL CH340 (COM3)`
- `USB Serial Port (COM4)`

### Flashear a la Placa

```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py -p COM5 flash
```

**Nota:** Reemplaza `COM5` con tu puerto serial detectado.

**⚠️ Si falla el flasheo con error de modo de arranque:**

1. **Primer intento:** Usa velocidad más lenta:
   ```powershell
   & "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py -p COM5 -b 115200 flash
   ```

2. **Si persiste el problema:** Usa esptool directamente:
   ```powershell
   & "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; python -m esptool --chip esp32 -p COM5 -b 115200 --before default_reset --after hard_reset write_flash --flash_mode dio --flash_freq 40m --flash_size 2MB 0x1000 build\bootloader\bootloader.bin 0x8000 build\partition_table\partition-table.bin 0x10000 build\ESP32_PLC-in-DC_Kiro.bin
   ```

3. **Método manual:** Mantén presionado el botón BOOT de la placa mientras ejecutas el comando de flasheo.

O usa el comando de Kiro: `ESP-IDF: Flash Device`

### Monitor Serial

```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py -p COM5 monitor
```

O usa el comando de Kiro: `ESP-IDF: Monitor Device`

### Todo en Uno

```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py -p COM5 build flash monitor
```

## Código de Ejemplo

El proyecto incluye un ejemplo básico que hace parpadear el LED integrado:

```cpp
#include "Arduino.h"

extern "C" void app_main()
{
    initArduino();
    pinMode(2, OUTPUT);  // GPIO2 es el LED integrado

    while(true) {
        digitalWrite(2, HIGH);  // Encender LED
        delay(500);             // Esperar 500ms
        digitalWrite(2, LOW);   // Apagar LED
        delay(500);             // Esperar 500ms
    }
}
```

## Personalización

### Cambiar el Pin del LED

Si tu placa usa un GPIO diferente para el LED integrado, modifica el número en `main.cpp`:

```cpp
pinMode(TU_GPIO_AQUI, OUTPUT);
digitalWrite(TU_GPIO_AQUI, HIGH);
digitalWrite(TU_GPIO_AQUI, LOW);
```

### Agregar Más Funcionalidad

Puedes usar todas las funciones de Arduino habituales:

- `analogRead()`, `analogWrite()`
- `Serial.begin()`, `Serial.print()`
- `WiFi.begin()`, `WiFi.connect()`
- Y muchas más...

## Configuración Avanzada

### Modificar Configuración del SDK

```powershell
& "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py menuconfig
```

Esto abre un menú de configuración donde puedes:

- Ajustar configuraciones de WiFi
- Modificar configuraciones de memoria
- Habilitar/deshabilitar componentes
- Y mucho más

### Agregar Componentes Adicionales

Para agregar componentes de ESP-IDF, modifica el archivo `main/CMakeLists.txt`:

```cmake
idf_component_register(SRCS "main.cpp"
                       INCLUDE_DIRS "."
                       REQUIRES arduino-esp32 tu_componente_aqui)
```

## Solución de Problemas

### Error de Dependencia Arduino (YA SOLUCIONADO)

Si obtienes errores de compilación relacionados con funciones de Arduino no encontradas, verifica que el archivo `main/CMakeLists.txt` contenga:

```cmake
idf_component_register(
    SRCS "main.cpp"
    INCLUDE_DIRS ""
    REQUIRES arduino-esp32  # CRÍTICO: Requerido para funciones Arduino
)
```

**Nota:** Este template ya incluye la configuración correcta. Si modificas el archivo, asegúrate de mantener la línea `REQUIRES arduino-esp32`.

### Error de FreeRTOS (YA SOLUCIONADO)

Si obtienes el error:

```
esp32-arduino requires CONFIG_FREERTOS_HZ=1000 (currently 100)
```

**Nota:** Este template ya tiene la configuración correcta (`CONFIG_FREERTOS_HZ=1000`) en el archivo `sdkconfig`. Si aún ves este error, verifica que el archivo `sdkconfig` esté presente y contenga la línea correcta.

### Error de Compilación

- Verifica que ESP-IDF esté correctamente instalado
- Asegúrate de haber seleccionado el target correcto
- Revisa que todas las dependencias estén instaladas

### Error de Flash

#### Error: "Wrong boot mode detected (0x13)"
```
A fatal error occurred: Failed to connect to ESP32: Wrong boot mode detected (0x13)! 
The chip needs to be in download mode.
```

**Soluciones en orden de prioridad:**

1. **Usar velocidad más lenta:**
   ```powershell
   & "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; idf.py -p COM5 -b 115200 flash
   ```

2. **Usar esptool directamente:**
   ```powershell
   & "$env:USERPROFILE\esp\v5.4.2\esp-idf\export.ps1"; python -m esptool --chip esp32 -p COM5 -b 115200 --before default_reset --after hard_reset write_flash --flash_mode dio --flash_freq 40m --flash_size 2MB 0x1000 build\bootloader\bootloader.bin 0x8000 build\partition_table\partition-table.bin 0x10000 build\ESP32_PLC-in-DC_Kiro.bin
   ```

3. **Método manual:** Mantén presionado el botón BOOT mientras ejecutas el flasheo.

#### Error: "The chip stopped responding"
Si el chip se conecta pero se detiene durante la configuración del flash:
- Usa esptool directamente (comando del punto 2 anterior)
- Verifica la calidad del cable USB (debe soportar datos, no solo carga)
- Intenta con un cable USB diferente

#### Error: "Could not open COM port"
- Verifica que la placa esté conectada correctamente
- Asegúrate de que el puerto serie sea el correcto usando: `Get-PnpDevice -Class Ports -Status OK`
- Cierra otros programas que puedan estar usando el puerto (Arduino IDE, PuTTY, etc.)
- Desconecta y reconecta el cable USB

### El LED No Parpadea

- Verifica que estés usando el GPIO correcto para tu placa
- Algunos ESP32 usan GPIO2, otros GPIO8 o GPIO10
- Consulta la documentación de tu placa específica

## Recursos Útiles

- [Documentación ESP-IDF](https://docs.espressif.com/projects/esp-idf/)
- [Arduino-ESP32 GitHub](https://github.com/espressif/arduino-esp32)
- [Guías ESP32](https://randomnerdtutorials.com/getting-started-with-esp32/)

## Contribuir

Si encuentras mejoras para esta plantilla, siéntete libre de sugerir cambios o crear un fork del proyecto.

## Licencia

Este proyecto es de dominio público. Úsalo libremente para tus proyectos.

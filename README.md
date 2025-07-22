# ESP-IDF con Arduino Template para Kiro

Esta es una plantilla base para proyectos ESP-IDF que utiliza Arduino como componente, optimizada para trabajar con Kiro IDE.

## Características

- **ESP-IDF Framework**: Utiliza el framework oficial de Espressif
- **Arduino como Componente**: Permite usar las funciones familiares de Arduino (digitalWrite, pinMode, delay, etc.)
- **Configuración Lista**: Proyecto preconfigurado y listo para usar
- **LED Integrado**: Ejemplo básico que hace parpadear el LED integrado (GPIO2)

## Estructura del Proyecto

```
├── main/
│   ├── main.cpp          # Código principal de la aplicación
│   └── CMakeLists.txt    # Configuración de compilación para main
├── CMakeLists.txt        # Configuración principal del proyecto
├── sdkconfig             # Configuración del SDK (generado automáticamente)
└── README.md            # Este archivo
```

## Requisitos Previos

1. **ESP-IDF**: Versión 4.4 o superior
2. **Extensión ESP-IDF**: Instalada en Kiro IDE
3. **Hardware**: Cualquier placa ESP32 compatible

## Configuración Inicial

### 1. Configurar ESP-IDF en Kiro

1. Abre la paleta de comandos (`Ctrl+Shift+P`)
2. Busca "ESP-IDF: Configure ESP-IDF Extension"
3. Sigue las instrucciones para configurar tu instalación de ESP-IDF

### 2. Seleccionar Target

1. Abre la paleta de comandos
2. Ejecuta "ESP-IDF: Set Espressif Device Target"
3. Selecciona tu modelo de ESP32 (esp32, esp32s2, esp32s3, esp32c3, etc.)

## Uso

### Compilar el Proyecto

```bash
idf.py build
```

O usa el comando de Kiro: `ESP-IDF: Build Project`

### Flashear a la Placa

```bash
idf.py flash
```

O usa el comando de Kiro: `ESP-IDF: Flash Device`

### Monitor Serial

```bash
idf.py monitor
```

O usa el comando de Kiro: `ESP-IDF: Monitor Device`

### Todo en Uno

```bash
idf.py build flash monitor
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

```bash
idf.py menuconfig
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

### Error de FreeRTOS
Si obtienes el error:
```
esp32-arduino requires CONFIG_FREERTOS_HZ=1000 (currently 100)
```
**Solución:** Cambia en el archivo `sdkconfig` la línea:
```
CONFIG_FREERTOS_HZ=100
```
Por:
```
CONFIG_FREERTOS_HZ=1000
```

### Error de Compilación
- Verifica que ESP-IDF esté correctamente instalado
- Asegúrate de haber seleccionado el target correcto
- Revisa que todas las dependencias estén instaladas

### Error de Flash
- Verifica que la placa esté conectada correctamente
- Asegúrate de que el puerto serie sea el correcto
- Intenta presionar el botón BOOT mientras flasheas

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
---
inclusion: always
---
# C++ Best Practices for ESP32 with ESP-IDF and Kiro

This file defines guidelines for programming in C++ for ESP-IDF projects using Kiro IDE. These practices ensure that the code is robust, maintainable, and efficient, optimized for the ESP32 microcontroller. All Kiro responses, generated code, and suggestions must adhere to these rules and be in English.

## Communication Guidelines
- **Language**: All Kiro responses, including explanations, code comments, and debug messages, must be in English.
- Use a clear, professional, and concise tone, suitable for developers with intermediate experience in C++ and ESP-IDF.

## C++ Programming Best Practices

### 1. Code Style and Formatting
- **Naming Conventions**:
  - Use `camelCase` for variable and function names (e.g., `ledTask`, `configureWifi`).
  - Use `SCREAMING_SNAKE_CASE` for constants and macros (e.g., `LED_GPIO`).
  - Prefer descriptive names in English, aligning with ESP-IDF conventions (e.g., `initGpio` instead of `initializeGpio`).
- **Comments**:
  - Include comments in English to explain the logic of each function, class, or significant code block.
  - Use single-line comments (`//`) for specific details and block comments (`/* */`) for function or module descriptions.
  - Example:
    ```cpp
    // Configure GPIO as output
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);
    ```
- **Formatting**:
  - Use `clang-format` with the LLVM style to format code automatically.
  - Use 4-space indentation and avoid tabs.
- **Line Length**: Limit lines to 120 characters for improved readability.

### 2. Code Structure
- **Modularity**:
  - Split code into separate files for each component (e.g., `led.cpp`, `wifi.cpp`).
  - Use a `main.cpp` file for the `app_main()` function required by ESP-IDF.
- **Classes and Objects**:
  - Use C++ classes to encapsulate related functionality (e.g., a `LedController` class for LED operations).
  - Prefer passing by reference (`&`) for large objects to avoid copies.
  - Example:
    ```cpp
    class LedController {
    private:
        gpio_num_t gpioPin;

    public:
        LedController(gpio_num_t pin) : gpioPin(pin) {
            // Initialize GPIO as output
            gpio_reset_pin(gpioPin);
            gpio_set_direction(gpioPin, GPIO_MODE_OUTPUT);
        }

        void toggle() {
            // Toggle LED state
            static bool state = false;
            gpio_set_level(gpioPin, state ? 1 : 0);
            state = !state;
        }
    };
    ```
- **Namespaces**: Use `namespace` to avoid name collisions, especially in larger projects.
  - Example:
    ```cpp
    namespace Esp32App {
        void initHardware();
    }
    ```

### 3. Resource Management
- **Memory**:
  - Avoid dynamic allocation (`new`/`delete`) on ESP32 due to limited memory. Use FreeRTOS heap (`heap_caps_malloc`) if necessary.
  - Explicitly free resources in class destructors.
- **FreeRTOS**:
  - Use FreeRTOS tasks (`xTaskCreate`) for concurrency.
  - Allocate sufficient stack sizes (e.g., 2048 bytes for simple tasks).
  - Example:
    ```cpp
    void ledTask(void* pvParameters) {
        LedController led(GPIO_NUM_2);
        while (true) {
            led.toggle();
            vTaskDelay(1000 / portTICK_PERIOD_MS); // Wait 1 second
        }
    }

    void app_main() {
        xTaskCreate(ledTask, "ledTask", 2048, nullptr, 5, nullptr);
    }
    ```

### 4. Error Handling
- **Error Codes**:
  - Use `esp_err_t` for handling ESP-IDF API errors.
  - Check return values of critical functions and handle errors in English.
  - Example:
    ```cpp
    esp_err_t result = esp_wifi_init(&cfg);
    if (result != ESP_OK) {
        // Error initializing Wi-Fi
        printf("Error: Failed to initialize Wi-Fi (%s)\n", esp_err_to_name(result));
        return;
    }
    ```
- **Exceptions**: Avoid using exceptions (`throw`/`catch`) on ESP32, as they are not supported by FreeRTOS by default.

### 5. Security
- **Sensitive Data**:
  - Do not include passwords, SSIDs, or other sensitive data in source code.
  - Use environment variables or configuration files (excluded via `.gitignore`).

### 6. Debugging
- **Logs**:
  - Use `ESP_LOGI`, `ESP_LOGE`, etc., for logging information.
  - Example:
    ```cpp
    #include "esp_log.h"
    static const char* TAG = "ESP32App";
    ESP_LOGI(TAG, "Starting LED task");
    ```
- **Monitoring**: Run `idf.py monitor` to debug serial output.
- **Common Errors**:
  - "undefined reference": Ensure necessary headers (e.g., `#include "driver/gpio.h"`) are included.

### 7. Project Organization
- **Structure**:
  - Place main code in `main/`.
  - Use `components/` for reusable modules.
  - Include a `CMakeLists.txt` for each component.
- **Example main.cpp**:
  ```cpp
  #include <stdio.h>
  #include "freertos/FreeRTOS.h"
  #include "freertos/task.h"
  #include "driver/gpio.h"
  #include "esp_log.h"

  static const char* TAG = "ESP32App";

  class LedController {
  private:
      gpio_num_t gpioPin;

  public:
      LedController(gpio_num_t pin) : gpioPin(pin) {
          // Initialize GPIO as output
          gpio_reset_pin(gpioPin);
          gpio_set_direction(gpioPin, GPIO_MODE_OUTPUT);
      }

      void toggle() {
          // Toggle LED state
          static bool state = false;
          gpio_set_level(gpioPin, state ? 1 : 0);
          state = !state;
      }
  };

  void ledTask(void* pvParameters) {
      LedController led(GPIO_NUM_2);
      while (true) {
          led.toggle();
          ESP_LOGI(TAG, "LED state changed");
          vTaskDelay(1000 / portTICK_PERIOD_MS);
      }
  }

  extern "C" void app_main() {
      // Create LED task
      xTaskCreate(ledTask, "ledTask", 2048, nullptr, 5, nullptr);
  }
  ```

### 9. References
- **ESP-IDF Documentation**: [https://docs.espressif.com/projects/esp-idf/en/latest/esp32/](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)
- **C++ Guide for ESP-IDF**: [https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/cplusplus.html](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/cplusplus.html)
- **LLVM Coding Style**: [https://llvm.org/docs/CodingStandards.html](https://llvm.org/docs/CodingStandards.html)
/**
 * ESP32 Arduino-IDF Template
 * 
 * Template with intelligent personalization and zero-setup configuration
 * Developed with Kiro IDE
 * 
 * @author Edwin González
 * @github https://github.com/edslogia
 * @linkedin https://www.linkedin.com/in/edwin-gonzalez-959829358/
 * @twitter @edwin91gc
 */

#include "Arduino.h"

extern "C" void app_main()
{
    initArduino();
    pinMode(2, OUTPUT);
    
    // LED flashing loop with 500ms intervals
    while(true) {
        digitalWrite(2, HIGH);  // Turn LED on
        delay(500);             // Wait 500ms
        digitalWrite(2, LOW);   // Turn LED off
        delay(500);             // Wait 500ms
    }
}
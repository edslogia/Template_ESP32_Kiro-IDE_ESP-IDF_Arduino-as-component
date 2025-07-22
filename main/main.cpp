#include "Arduino.h"

extern "C" void app_main()
{
    initArduino();
    pinMode(4, OUTPUT);
    
    // LED flashing loop with 500ms intervals
    while(true) {
        digitalWrite(4, HIGH);  // Turn LED on
        delay(500);             // Wait 500ms
        digitalWrite(4, LOW);   // Turn LED off
        delay(500);             // Wait 500ms
    }
}
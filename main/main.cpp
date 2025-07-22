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
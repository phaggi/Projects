#include <Arduino.h>

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
    delay(1000);
} 
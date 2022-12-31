#pragma once
#include <Arduino.h>

#define FUEL_INJECTOR_OPEN_DELAY_MS 100
#define FUEL_INJECTOR_OPEN_TIME_MS 10

bool fuel_injector_open = false;

void init_fuel_injector() {
    pinMode(FUEL_INJECTOR_PIN, OUTPUT);
    pinMode(FUEL_INJECTOR_START_PIN, INPUT_PULLUP);
    digitalWrite(FUEL_INJECTOR_PIN, LOW);
}

bool is_triggered() {
    return digitalRead(FUEL_INJECTOR_START_PIN) == LOW;
}

void fuel_injector_loop() {
    if (is_triggered()) {
        delay(FUEL_INJECTOR_OPEN_DELAY_MS);
        digitalWrite(FUEL_INJECTOR_PIN, HIGH);
        delay(FUEL_INJECTOR_OPEN_TIME_MS);
        digitalWrite(FUEL_INJECTOR_PIN, LOW);

        while(is_triggered()) {
            delay(10);
        }
    }
}
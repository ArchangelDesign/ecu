#pragma once
#include <Arduino.h>

#define FUEL_INJECTOR_OPEN_DELAY_MS 100
#define FUEL_INJECTOR_OPEN_TIME_MS 10
#define FUEL_INJECTOR_CYCLES 5

bool state_is_fuel_injector_open = false;
bool state_is_red_button_down = false;
unsigned long red_button_press_time = 0;
unsigned long red_button_release_time = 0;

void init_fuel_injector() {
    pinMode(FUEL_INJECTOR_PIN, OUTPUT);
    pinMode(FUEL_INJECTOR_START_PIN, INPUT_PULLUP);
    pinMode(FUEL_INJECTOR_LONG_START_PIN, INPUT_PULLUP);
    digitalWrite(FUEL_INJECTOR_PIN, LOW);
}

void reset_red_button() {
    red_button_press_time = 0;
    red_button_release_time = 0;
}

bool is_blue_button_down() {
    return digitalRead(FUEL_INJECTOR_START_PIN) == LOW;
}

bool is_red_button_down() {
    return digitalRead(FUEL_INJECTOR_LONG_START_PIN) == LOW;
}

void open_fuel_injector() {
    digitalWrite(FUEL_INJECTOR_PIN, HIGH);
    state_is_fuel_injector_open = true;
}

void close_fuel_injector() {
    digitalWrite(FUEL_INJECTOR_PIN, LOW);
    state_is_fuel_injector_open = false;
}

void trigger_fuel_injector_single_open_signal() {
    delay(FUEL_INJECTOR_OPEN_DELAY_MS);
    open_fuel_injector();
    delay(FUEL_INJECTOR_OPEN_TIME_MS);
    close_fuel_injector();
}

void trigger_fuel_injector_multiple_open_signal(const uint8_t times = 1) {
    for (int i = 0; i < times; i++) {
        open_fuel_injector();
        delay(FUEL_INJECTOR_OPEN_TIME_MS);
        close_fuel_injector();
        delay(FUEL_INJECTOR_OPEN_DELAY_MS);
    }
}

void fuel_injector_loop() {
    if (is_blue_button_down()) {
        // blue button pressed
        trigger_fuel_injector_single_open_signal();
        while (is_blue_button_down()) {
            delay(1);
        }
    }

    if (is_red_button_down() && !state_is_red_button_down) {
        state_is_red_button_down = true;
        red_button_press_time = millis();
    }
    
    if (!is_red_button_down() && state_is_red_button_down) {
        state_is_red_button_down = false;
        red_button_release_time = millis();
    }

    if (red_button_release_time > red_button_press_time) {
        // red button pressed
        uint16_t time_ms = red_button_release_time - red_button_press_time;
        if (time_ms <= 2000) {
            trigger_fuel_injector_multiple_open_signal(5);
            reset_red_button();
        }
        if (time_ms > 2000) {
            trigger_fuel_injector_multiple_open_signal(100);
            reset_red_button();
        }
    }
}
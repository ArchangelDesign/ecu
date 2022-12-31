#pragma once
#include <Arduino.h>
#include "throttle_control.h"

TaskHandle_t crankshaft_position_task;


double period = 1 / THROTTLE_FREQUENCY;
uint32_t min_delay_ms = period * 1000;
uint32_t max_delay_ms = min_delay_ms * THROTTLE_MAX_DUTY_CYCLE;
uint8_t throttlePercentage = (currentThrottlePosition * 100) / THROTTLE_MAX_DUTY_CYCLE;
uint32_t current_delay = (throttlePercentage / 100) * max_delay_ms;

void crankshaft_control_init() {
    pinMode(CRANKSHAFT_POSITION_PIN, OUTPUT);
}

void crankshaftPositionSignal(void * parameter) {
  for (;;) {
    digitalWrite(CRANKSHAFT_POSITION_PIN, LOW);
    delay(2);
    digitalWrite(CRANKSHAFT_POSITION_PIN, HIGH);
    delay(1);
  }
}
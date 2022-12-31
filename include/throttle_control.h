#pragma once
#include <Arduino.h>

TaskHandle_t throttlePositionSignalTask;
uint32_t currentThrottlePosition = 1;

#define THROTTLE_UP_DELAY_MS 10
#define THROTTLE_DOWN_DELAY_MS 8

void throttle_control_init() {
  ledcSetup(THROTTLE_PWM_CHANNEL, THROTTLE_FREQUENCY, THROTTLE_RESOLUTION);
  ledcAttachPin(THROTTLE_PIN, THROTTLE_PWM_CHANNEL);
}

void throttlePositionSignal(void * parameter) {
  for (;;) {
    ledcWrite(THROTTLE_PWM_CHANNEL, currentThrottlePosition);
    delay(THROTTLE_UP_DELAY_MS);
    currentThrottlePosition++;
    if (currentThrottlePosition >= THROTTLE_MAX_DUTY_CYCLE - 1) {
      while (currentThrottlePosition > 2) {
        currentThrottlePosition--;
        ledcWrite(THROTTLE_PWM_CHANNEL, currentThrottlePosition);
        delay(THROTTLE_DOWN_DELAY_MS);
      }
    }
  }
}
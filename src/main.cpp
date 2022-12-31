#include <Arduino.h>

#include "throttle_control.h"
#include "crankshaft_control.h"
#include "fuel_injector_signal.h"

void setup() {
  throttle_control_init();
  crankshaft_control_init();
  xTaskCreatePinnedToCore(
        throttlePositionSignal,
        "Throttle Control Signal",
        10000,
        NULL,
        1,
        &throttlePositionSignalTask,
        0
  );
  xTaskCreatePinnedToCore(
    crankshaftPositionSignal,
    "Crankshaft Position Signal",
    10000,
    NULL,
    1,
    &crankshaft_position_task,
    0
  );
  delay(500);
  init_fuel_injector();
}

void loop() {
  fuel_injector_loop();
}
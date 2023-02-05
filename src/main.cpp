#include <Arduino.h>
#include "state_handler.h"

void setup() {
  Serial.begin(115200);
  while (!Serial);
  setupInitialState();
}

void loop() {
  handleGlobalState();
}
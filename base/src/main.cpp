#include <Arduino.h>
#include "base.h"
// #include "receiver.h"

void setup() {
  setupTransmitter();
  // setupReceiver();
}

void loop() {
  transmitterLoop();
  // receiverLoop();
}
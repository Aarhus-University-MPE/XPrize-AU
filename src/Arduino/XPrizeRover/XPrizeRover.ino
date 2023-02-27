/*
  XPrize Rover mainframe
  - Manages primary systems

  Mads Rosenhøj Jepepsen
  Aarhus University
  2023
*/

#include "./modules/setup/modules.h"

void setup() {
  InitializeDebugComm();

  delay(150);

  // System initialization
  InitAllPins();

  delay(150);

  InitializeMotors();
  DEBUG_PRINTLN(F("Initialized!"));
}

void loop() {
  // USB debug commands
  // DBG_ONLY(recvWithStartEndMarkers());
}

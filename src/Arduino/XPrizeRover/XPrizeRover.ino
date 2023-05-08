/*
  XPrize Rover mainframe
  - Manages primary systems

  Mads Rosenhøj Jeppesen
  Aarhus University
  2023
*/

#include "./modules/setup/modules.h"

void setup() {
  // Serial Communication
  DBG_ONLY(InitializeDebugComm());

  delay(150);

  // System initialization
  InitAllPins();

  delay(150);
  DEBUG_PRINTLN(F("Initialized!"));
}

void loop() {
  // USB debug commands
  DBG_ONLY(recvWithStartEndMarkers());
}

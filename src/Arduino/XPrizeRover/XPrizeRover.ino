/*
  XPrize Rover mainframe
  - Manages primary systems

  Mads Rosenhøj Jeppesen
  Aarhus University
  2023
*/

#include "./modules/setup/modules.h"

void setup() {
  // System initialization
  SystemEnablePrimary();

  delay(150);
}

void loop() {
  PowerFlagProcess();

  // Check system online
  if (!GetSystemState()) return;
  digitalWrite(LED_BUILTIN, true);

  // Process secondary system
  SbusProcess();
  TelemetryProcess();
}

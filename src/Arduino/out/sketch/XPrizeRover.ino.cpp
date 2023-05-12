#include <Arduino.h>
#line 1 "D:\\Projects\\XPrize-AU\\src\\Arduino\\XPrizeRover\\XPrizeRover.ino"
/*
  XPrize Rover mainframe
  - Manages primary systems

  Mads Rosenhøj Jeppesen
  Aarhus University
  2023
*/

#include "./modules/setup/modules.h"

#line 12 "D:\\Projects\\XPrize-AU\\src\\Arduino\\XPrizeRover\\XPrizeRover.ino"
void setup();
#line 19 "D:\\Projects\\XPrize-AU\\src\\Arduino\\XPrizeRover\\XPrizeRover.ino"
void loop();
#line 12 "D:\\Projects\\XPrize-AU\\src\\Arduino\\XPrizeRover\\XPrizeRover.ino"
void setup() {
  // System initialization
  SystemEnablePrimary();

  delay(150);
}

void loop() {
  PowerFlagProcess();

  // Check system online
  if (!GetSystemState()) return;

  // Process secondary system
  SbusProcess();
  TelemetryProcess();
}


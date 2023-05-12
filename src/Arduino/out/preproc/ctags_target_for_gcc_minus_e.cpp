# 1 "D:\\Projects\\XPrize-AU\\src\\Arduino\\XPrizeRover\\XPrizeRover.ino"
/*

  XPrize Rover mainframe

  - Manages primary systems



  Mads Rosenhøj Jeppesen

  Aarhus University

  2023

*/
# 10 "D:\\Projects\\XPrize-AU\\src\\Arduino\\XPrizeRover\\XPrizeRover.ino"
# 11 "D:\\Projects\\XPrize-AU\\src\\Arduino\\XPrizeRover\\XPrizeRover.ino" 2

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

/*
  GeoRover System control

  Mads Rosenhøj Jeppesen
  Aarhus University
  2021
*/

#pragma once
#include "../setup/modules.h"

bool powerFlag = false;

unsigned long millisLastPowerFlagUpdate = 0;

// Disables secondary systems
void PowerFlagProcess() {
  if (millis() - millisLastPowerFlagUpdate < POWERFLAG_PERIOD) return;
  millisLastPowerFlagUpdate = millis();

  powerFlag = analogRead(PI_POWER_FLAG) > 800;

  // Check if current state matches powerFlag
  if (powerFlag == digitalRead(PO_SYSTEM_EN)) return;

  if (powerFlag) {
    SystemEnableSecondary();
  } else {
    SystemDisableSecondary();
  }
}

// Return current system status
bool GetSystemState() {
  return powerFlag;
}

// Enables Primary Systems
void SystemEnablePrimary() {
  InitAllPins();
}

// Disable Secondary Systems
void SystemDisableSecondary() {
  digitalWrite(PO_SYSTEM_EN, false);
}

// Enables Secondary Systems
void SystemEnableSecondary() {
  digitalWrite(PO_SYSTEM_EN, true);

  ImuInitialize();
  // SDReaderInitialize();
  SbusInitialize();
  TelemetryInitialize();
  GnssInitialize();
}

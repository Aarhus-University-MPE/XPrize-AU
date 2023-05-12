/*
  XPrize Rover System control

  Mads Rosenhøj Jeppesen
  Aarhus University
  2023
*/

#pragma once
#include "../setup/modules.h"

bool powerFlag   = false;
bool powerDetect = false;

unsigned long millisLastPowerFlagUpdate = 0;
unsigned long lastMillisFlag            = 0;

// Disables secondary systems
void PowerFlagProcess() {
  if (millis() - millisLastPowerFlagUpdate < POWERFLAG_PERIOD) return;
  millisLastPowerFlagUpdate = millis();

  powerFlag = analogRead(PI_POWER_FLAG) > 500;

  // Check if current state matches powerFlag
  if (powerFlag == digitalRead(PO_SYSTEM_EN)) {
    powerDetect = false;
    return;
  }

  // Skip first detection
  if (!powerDetect) {
    powerDetect = true;
    return;
  }

  // Enable/Disable power
  if (powerFlag) {
    SystemEnableSecondary();
  } else {
    SystemDisableSecondary();
  }

  powerDetect = false;
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

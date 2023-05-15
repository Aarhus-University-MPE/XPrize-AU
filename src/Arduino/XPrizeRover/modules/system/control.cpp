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
unsigned long lastMillisWake            = -POWER_WAKE_DURATION;

// Disables secondary systems
void PowerFlagProcess() {
  if (millis() - millisLastPowerFlagUpdate < POWERFLAG_PERIOD) return;
  millisLastPowerFlagUpdate = millis();

  powerFlag = analogRead(PI_POWER_FLAG) > 800;

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

// Sleep for x times 9 seconds, (rounded down)
void SleepDuration(uint16_t seconds) {
  uint16_t sleepCycles = seconds / 9;  // 8 sec sleep + 1 sec wakeup time
  digitalWrite(LED_BUILTIN, true);
  for (size_t i = 0; i < sleepCycles; i++) {
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }
  lastMillisWake = millis();
  digitalWrite(LED_BUILTIN, false);
}

void StandbyMode(int8_t sleep) {
  if (sleep < 80) return;
  if (millis() - lastMillisWake < POWER_WAKE_DURATION) return;

  SystemDisableSecondary();
  SleepDuration(POWER_DOWN_DURATION);
}

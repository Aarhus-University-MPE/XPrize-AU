/*
  GeoRover System control

  Mads Rosenhøj Jepepsen
  Aarhus University
  2021
*/

#pragma once
#include "../setup/modules.h"

// Disables secondary systems
void ModuleDisable() {
  // ModuleDisable(MODULE_PWR_MOTOR);
  // ModuleDisable(MODULE_PWR_CANISTER);
  // ModuleDisable(MODULE_MOTOR);
  // ModuleDisable(MODULE_CLOCK);
  // ModuleDisable(MODULE_COMM_LORA);
  // ModuleDisable(MODULE_COMM_CANISTER);
}

// Enables Primary Systems
void SystemEnablePrimary() {
  // ModuleEnable(MODULE_SD);
  // ModuleEnable(MODULE_BLACKBOX);
}

// Run full system check
void SystemTest(bool printRes) {
  // SetStatus(MODULE_PWR_PRIMARY, BatteryStatus());
  // SetStatus(MODULE_PWR_MOTOR, GetStatus(MODULE_PWR_MOTOR));
  // SetStatus(MODULE_PWR_CANISTER, GetStatus(MODULE_PWR_CANISTER));
  // SetStatus(MODULE_MOTOR, MotorStatus());
  // SetStatus(MODULE_SD, SDReaderStatus());
  // SetStatus(MODULE_CLOCK, RTCStatus());
  // SetStatus(MODULE_COMM_LORA, LoraStatus());
  // SetStatus(MODULE_COMM_CANISTER, CanisterCommStatus());
  // SetStatus(MODULE_COMM_DBG, DebugCommStatus());
  // SetStatus(MODULE_BLACKBOX, BlackBoxStatus());
  // SetStatus(MODULE_RESERVED, true);
}
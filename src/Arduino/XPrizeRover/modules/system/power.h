/*
  Lake Profiler Power control

  Mads Rosenhøj Jeppesen
  Aarhus University
  2022
*/

#pragma once

#include "../setup/modules.h"

// BatteryReading = 3 kOhm / (3 kOhm + 9 kOhm) * Battery Voltage
// 12.6V .. 10.5V -> ~3.15V .. 2.65V -> 645 .. 542
const float batteryScaleA = 28.722f;
const float batteryScaleB = -617.39f;
const float batteryOffset = 3318.3f;

const float minVoltage = 10.0f;
const float maxVoltage = 18.0f;

const float batteryVoltageOffset = 0.1f;

int BatteryLevel() {
  float batteryVoltage = BatteryVoltage();

  // Check over/under charged
  if (batteryVoltage < minVoltage) return 0;
  if (batteryVoltage > maxVoltage) return 100;

  float batteryLevel = batteryScaleA * batteryVoltage * batteryVoltage + batteryScaleB * batteryVoltage + batteryOffset;

  return (int)batteryLevel;
}

// Return battery Level in Hex
uint8_t BatteryLevelHex() {
  return (uint8_t)BatteryLevel();
}

// Return battery voltage *10 in Hex
uint8_t BatteryVoltageHex() {
  return (uint8_t)(BatteryVoltage() * 10.0f);
}

// Checks voltage levels above critical values?
bool VoltageCheck() {
  return BatteryLevel() > GetBatteryMinLevel();
}

float BatteryVoltage() {
  int voltageInt = analogRead(PA_SENSOR_BATT);

  float voltageRead = voltageInt * 5.0f / 1024.0f;

  float voltageBattery = voltageRead * 12.0f / 3.0f + batteryVoltageOffset;

  return voltageBattery;
}

// Returns current battery status > minimum battery level
bool BatteryStatus() {
  return VoltageCheck();
}

bool BatteryStatus(bool print) {
  if (!print) {
    return VoltageCheck();
  }

  DEBUG_PRINT(F("Battery Level: "));
  DEBUG_PRINTLN(BatteryLevel());

  DEBUG_PRINT(F("Battery Voltage: "));
  DEBUG_PRINTLN(BatteryVoltage());
  return VoltageCheck();
}

void StandbyMode() {
  // LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
}

void wakeUp() {
  // Just a handler for the pin interrupt.
}

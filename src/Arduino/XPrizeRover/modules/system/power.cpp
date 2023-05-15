/*
  XPrize Rover Power control

  Mads Rosenhøj Jeppesen
  Aarhus University
  2023
*/

#pragma once

#include "../setup/modules.h"

const float R2 = 31.165;  // 33k Ohm
const float R1 = 510;     // 510 kOhmn

const float acdcFactor     = (5.0f / 1024.0f);
const float voltageDividor = R2 / (R1 + R2);

#ifdef BATTERY_TYPE_NIMH
const float a3            = -65.595f;
const float a2            = 3452.9f;
const float a1            = -60503.0f;
const float a0            = 352955.0f;
const float minBatVoltage = 16.97f;
const float maxBatVoltage = 18.06f;
const float voltageSag    = 1.2f;  // Voltage Sag under avg load
#endif
#ifdef BATTERY_TYPE_LIPO
const float a3            = 5.3668f;
const float a2            = -269.76f;
const float a1            = 4543.8f;
const float a0            = -25548.0f;
const float minBatVoltage = 15.0f;  // 3.6 V per cell cutoff
const float maxBatVoltage = 16.44f;
const float voltageSag    = 0.0f;  // Voltage Sag under avg load
#endif

// Returns current battery level
// Estimated with level = -65,595 x Voltage^3 + 3452,9 x Voltage^2 - 60503 x Voltage + 352955 (range 20-90 %)
uint8_t BatteryLevel() {
  float batteryVoltage = BatteryVoltage();

  // Check over/under charged
  if (batteryVoltage < minBatVoltage) return 1;
  if (batteryVoltage > maxBatVoltage) return 100;

  float batteryLevel = a3 * pow(batteryVoltage, 3) + a2 * pow(batteryVoltage, 2) + a1 * batteryVoltage + a0;

  return (uint8_t)batteryLevel;
}

// Returns battery voltage x 1000 as an integer
int16_t BatteryVoltageInt() {
  return (int16_t)(BatteryVoltage() * 1000.0f);
}

// Returns battery voltage as a float
float BatteryVoltage() {
  analogReference(DEFAULT);    // Set analog reference to internal for 1.1 voltage vMax
  analogRead(PA_SENSOR_BATT);  // Discard first reading
  delay(10);                   // Delay first reading

  // Read and convert analog battery voltage
  uint16_t read        = analogRead(PA_SENSOR_BATT);
  float voltageAcdc    = read * acdcFactor;
  float voltageBattery = voltageAcdc / voltageDividor;

  analogReference(DEFAULT);  // Reset analog reference to default 5.0 voltage vMax

  return voltageBattery;
}

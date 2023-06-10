/*
  XPrize Rover Function Templates protocols

  Mads Rosenhøj Jeppesen
  Aarhus University
  2023
*/

#pragma once

#include "./modules.h"

// System
void (*systemReset)(void) = 0;
void InitAllPins();
void InitSecondaryPins();
void TerminateSecondaryPins();
void PowerFlagProcess();
void SystemEnableSecondary();
void SystemDisableSecondary();
bool GetSystemState();
void StandbyMode(int8_t sleep);

// Drivetrain
void DriveTrainInitialize();
void DriveTrainTerminate();
void DriveTrainProcess(int8_t throttle, int8_t steer, int8_t gear, int8_t headlights);

// Swapper
void SwapperInitialize();
void SwapperTerminate();
void SwapperProcess(int8_t select, int8_t arm, int8_t lid, int8_t airFilter);
void MoveLeftLid(bool open);
void MoveRightLid(bool openLid);

// SBUS
void SbusInitialize();
void SbusTerminate();
void SbusProcess();

// Telemetry
void TelemetryInitialize();
void TelemetryTerminate();
void TelemetryProcess();

// GNSS
void GnssTerminate();
void GnssInitialize();
int32_t GnssGetLat();
int32_t GnssGetLong();
uint8_t GnssGetSIV();
uint8_t GnssGetFixType();
float GnssGetHeading();

// IMU
void ImuInitialize();
void ImuTerminate();
void ImuUpdate();
float ImuHeading();
float ImuPitch();
float ImuRoll();

// USB Comm
bool DebugCommInitialize();

// Power
uint8_t BatteryLevel();
float BatteryVoltage();
void BatteryPrint();

// Servo Driver
unsigned long ServoProcess(Servo &servo, uint8_t angle, uint8_t servoPin, uint8_t lastAngle, unsigned long lastMillis);
void ServoProcess(Servo &servo, uint8_t angle, int servoPin, uint8_t servoPeriod = 25);
void ServoInitialize();
void ServoProcess(uint8_t channel, uint8_t angle, int8_t extended = 0);
void DisableServo(uint8_t channel);

// SD Reader
void SDReaderInitialize();

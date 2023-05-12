/*
  XPrize Rover SBUS communication, receive data from controller

  Mads Rosenhøj Jeppesen
  Aarhus University
  2023
*/

#pragma once

#include "../setup/modules.h"

SBUS sbus(COM_SBUS);

const uint16_t minChannel = 364;
const uint16_t maxChannel = 1684;

unsigned long millisLastSBusUpdate = 0;

void SbusInitialize() {
  sbus.begin(false);
}

// Scale the S.BUS channel values into the range [-100, 100]
int8_t getChannel(int channel) {
  uint16_t value = sbus.getChannel(channel);

  // Remap to between -100 and 100
  // int mappedValue = map(value, minChannel, maxChannel, -100, 100);

  return map(value, minChannel, maxChannel, -100, 100);
}

void SbusParse() {
  // Read and convert SBUS values to drivetrain controls
  int8_t steer      = getChannel(CHANNEL_STEER);
  int8_t throttle   = getChannel(CHANNEL_THROTTLE);
  int8_t gear       = getChannel(CHANNEL_GEAR);
  int8_t headlights = getChannel(CHANNEL_HEADLIGHTS);

  // Check for valid signal
  if (throttle > 100 || millis() - sbus.getLastTime() > SBUS_TIMEOUT) return;

  // Process drivetrain controls
  DriveTrainProcess(throttle, steer, gear, headlights);

  // Read and convert SBUS values to Swapper controls
  int8_t swapSelect = getChannel(CHANNEL_SWAPPER_SELECT);
  int8_t arm        = getChannel(CHANNEL_SWAPPER_ARM);
  int8_t lid        = getChannel(CHANNEL_SWAPPER_LID);

  // Process Swapper controls
  SwapperProcess(swapSelect, arm, lid);
}

void SbusProcess() {
  // Read SBUS channel NOTE: Must run often to avoid lost frames
  sbus.process();

  // Throttle SBUS updates too once per
  if (millis() - millisLastSBusUpdate < SBUS_PERIOD) return;

  millisLastSBusUpdate = millis();

  // Parse SBUS values to control variables
  SbusParse();
}

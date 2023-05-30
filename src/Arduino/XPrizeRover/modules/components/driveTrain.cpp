/*
  XPrize Rover drivetrain mainframe

  Mads Rosenhøj Jeppesen
  Aarhus University
  2023
*/

#pragma once

#include "../setup/modules.h"

// Servo Throttle, Steer, Gear;
Servo Throttle, Steer;

const uint8_t maxSteer = 180;
const uint8_t minSteer = 0;

uint8_t lastSteer      = 89;
const int8_t steerTrim = -18;

const float maxThrottleGainFwd = 1.0f;  // To avoid jitter overshooting ESC throttle limit
const float maxThrottleGainRev = 1.0f;  // To avoid jitter overshooting ESC throttle limit

const uint8_t maxThrottleIncrementFwd = 90 * maxThrottleGainFwd;
const uint8_t maxThrottleIncrementRev = 90 * maxThrottleGainRev;

unsigned long lastMillisSteer, lastMillisThrottle, lastMillisGear;

// Primary drive train process
void DriveTrainProcess(int8_t throttle, int8_t steer, int8_t gear, int8_t headlights) {
  throttle = constrain(throttle, -100, 100);
  steer    = constrain(steer + steerTrim, -100, 100);

  uint8_t _steer    = map(steer, -100, 100, minSteer, maxSteer);
  uint8_t _throttle = map(throttle, -100, 100, 90 - maxThrottleIncrementRev, 90 + maxThrottleIncrementFwd);

  // Steering
  ServoProcess(PWM_CHANNEL_STEER_L, constrain(_steer - 5, 0, 180));
  ServoProcess(PWM_CHANNEL_STEER_R, _steer);
  // lastMillisSteer = ServoProcess(Steer, _steer, PP_STEER, lastSteer, lastMillisSteer);
  // lastSteer       = _steer;

  // Throttle
  ServoProcess(PWM_CHANNEL_THROTTLE, _throttle);
  // ServoProcess(Throttle, _throttle, PP_THROTTLE);

  // Headlights
  digitalWrite(PO_HEADLIGHT_EN, headlights > 75);
}

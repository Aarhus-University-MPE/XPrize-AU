/*
  XPrize Rover drivetrain mainframe

  Mads Rosenhøj Jeppesen
  Aarhus University
  2023
*/

#pragma once

#include "../setup/modules.h"

Servo Throttle, Steer, Gear;

const uint8_t maxSteer = 180;
const uint8_t minSteer = 0;

uint8_t lastSteer = 89;

const float maxThrottleGainFwd        = 0.75f;  // To avoid jitter overshooting ESC throttle limit
const float maxThrottleGainRev        = 0.70f;  // To avoid jitter overshooting ESC throttle limit
const uint8_t maxThrottleIncrementFwd = 90 * maxThrottleGainFwd;
const uint8_t maxThrottleIncrementRev = 90 * maxThrottleGainRev;

unsigned long lastMillisSteer, lastMillisThrottle, lastMillisGear;

// TODO: Implement gear shift
// void SetGear(MotorGear gear) {
//   switch (gear) {
//     case Low:
//       Gear.write(45);
//       break;
//     case High:
//       Gear.write(45);
//       break;
//     default:
//       break;
//   }
// }

// Primary drive train process
void DriveTrainProcess(int8_t throttle, int8_t steer, int8_t gear, int8_t headlights) {
  throttle = constrain(throttle, -100, 100);
  steer    = constrain(steer, -100, 100);

  uint8_t _steer    = map(steer, -100, 100, minSteer, maxSteer);
  uint8_t _throttle = map(throttle, -100, 100, 90 - maxThrottleIncrementRev, 90 + maxThrottleIncrementFwd);

  // Steering
  lastMillisSteer = ServoProcess(Steer, _steer, PP_STEER, lastSteer, lastMillisSteer);
  lastSteer       = _steer;

  // Throttle
  ServoProcess(Throttle, _throttle, PP_THROTTLE);

  // Headlights
  digitalWrite(PO_HEADLIGHT_EN, headlights > 75);
}

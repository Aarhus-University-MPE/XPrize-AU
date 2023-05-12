#line 1 "D:\\Projects\\XPrize-AU\\src\\Arduino\\XPrizeRover\\modules\\components\\driveTrain.cpp"
/*
  XPrize Rover drivetrain mainframe

  Mads Rosenhøj Jeppesen
  Aarhus University
  2023
*/

#pragma once

#include "../setup/modules.h"

Servo Throttle, Steer, Gear;

const uint8_t maxSteer = 135;
const uint8_t minSteer = 45;

uint8_t lastSteer = 89;

const float maxThrottleGain        = 0.5f;
const uint8_t maxThrottleIncrement = 90 * 0.5f;

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
  uint8_t _steer    = map(steer, -100, 100, minSteer, maxSteer);
  uint8_t _throttle = map(throttle, -100, 100, 90 - maxThrottleIncrement, 90 + maxThrottleIncrement);

  // Steering
  lastMillisSteer = ServoProcess(Steer, _steer, PP_STEER, lastSteer, lastMillisSteer);
  lastSteer       = _steer;

  // Throttle
  ServoProcess(Throttle, _throttle, PP_THROTTLE);

  // Headlights
  digitalWrite(PO_HEADLIGHT_EN, headlights > 75);
}

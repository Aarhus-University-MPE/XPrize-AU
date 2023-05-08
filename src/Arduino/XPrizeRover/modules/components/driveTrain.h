/*
  XPrize Rover drivetrain mainframe

  Mads Rosenhøj Jeppesen
  Aarhus University
  2023
*/

#pragma once

#include "../setup/modules.h"

Servo Throttle, Steer, Gear;

// Initialize drive train
void InitializeDriveTrain() {
  // Attach PWM pins
  Throttle.attach(PP_THROTTLE);
  Steer.attach(PP_STEER);
  Gear.attach(PP_GEAR);

  // Initialize PWM values
  Throttle.write(90);
  Steer.write(90);
  Gear.write(90);
}

void SetGear(Gear gear) {
  switch (gear) {
    case Low:
      Gear.write(45);
      break;

    case High:
      Gear.write(45);
      break;
    default:
      break;
  }
}

// Move motors based on input, if
void MotorMove(uint8_t motor) {
  motorState[motor] = !motorState[motor];

  uint8_t angle = motorState[motor] == 1 ? 180 : 0;
  ArmLeft_Servo.write(angle);

  DEBUG_PRINT(F("Setting Angle of Motor "));
  DEBUG_PRINT(motor);
  DEBUG_PRINT(F(": "));
  DEBUG_PRINTLN(angle);
}

/*
  Lake Profiler Motor control

  Mads Rosenhøj Jepepsen
  Aarhus University
  2021
*/

#pragma once

#include "../setup/modules.h"

bool motorState[4] = {false, false, false, false};
Servo ArmLeft_Servo;  // create servo object to control a servo

// Initialize motors and turns on encoder power
bool InitializeMotors() {
  // Initialize outputs
  ArmLeft_Servo.attach(PO_MOTOR_ARM_LEFT);
  ArmLeft_Servo.write(0);

  return true;
}

// Disables motors and turns off encoder power
void TerminateMotors() {
  digitalWrite(PO_MOTOR_ARM_LEFT, LOW);
  digitalWrite(PO_MOTOR_ARM_RIGHT, LOW);
  digitalWrite(PO_MOTOR_LATCH_LEFT, LOW);
  digitalWrite(PO_MOTOR_LATCH_RIGHT, LOW);
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

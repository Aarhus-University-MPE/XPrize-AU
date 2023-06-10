/*
  XPrize Rover eDNA swapper

  Mads Rosenhøj Jeppesen
  Aarhus University
  2023
*/

#pragma once

#include "../setup/modules.h"

bool lidOpenL     = false;
bool lidOpenR     = false;
bool selectDetect = false;
bool filterActive = false;

const uint8_t lidOpenPosLeft   = 130;
const uint8_t lidClosedPosLeft = 0;
const uint8_t lidOpenSizeLeft  = lidOpenPosLeft - lidClosedPosLeft;

const uint8_t lidOpenPosRight   = 130;
const uint8_t lidClosedPosRight = 10;
const uint8_t lidOpenSizeRight  = lidOpenPosRight - lidClosedPosRight;

const uint8_t angleRev = 10;
const uint8_t angleFwd = 170;

const int8_t servoExtend = 40;

const float angleResolution = 45;

const int8_t armTrimLeft  = -3;
const int8_t armTrimRight = 0;

// Initialize Servo Positions
void SwapperInitialize() {
  ServoProcess(PWM_CHANNEL_LID_L, lidClosedPosLeft, servoExtend);
  ServoProcess(PWM_CHANNEL_LID_R, lidClosedPosRight, servoExtend);
  ServoProcess(PWM_CHANNEL_ARM_L, 90 + armTrimLeft);
  ServoProcess(PWM_CHANNEL_ARM_R, 90 + armTrimRight);
}

// Enable/Disable air filter
void AirFilter(bool enable) {
  if (filterActive == enable) return;
  filterActive = enable;
  digitalWrite(PO_AIRFILTER_EN, enable);
}

// Open/Close Left lid
void MoveLeftLid(bool openLid) {
  float angle;
  float angleIncrements;

  if (openLid) {  // Open lid
    angle           = lidClosedPosLeft;
    angleIncrements = lidOpenSizeLeft / angleResolution;
  } else {  // Close lid
    angle           = lidOpenPosLeft;
    angleIncrements = -lidOpenSizeLeft / angleResolution;
  }

  for (size_t i = 0; i < angleResolution; i++) {
    angle += angleIncrements;
    ServoProcess(PWM_CHANNEL_LID_L, (uint8_t)angle, servoExtend);
    delay(10);
  }

  lidOpenL = openLid;
}

// Open/Close Right lid
void MoveRightLid(bool openLid) {
  float angle;
  float angleIncrements;

  if (openLid) {  // Open lid
    angle           = lidClosedPosRight;
    angleIncrements = lidOpenSizeRight / angleResolution;
  } else {  // Close lid
    angle           = lidOpenPosRight;
    angleIncrements = -lidOpenSizeRight / angleResolution;
  }

  for (size_t i = 0; i < angleResolution; i++) {
    angle += angleIncrements;
    ServoProcess(PWM_CHANNEL_LID_R, (uint8_t)angle, servoExtend);
    delay(10);
  }

  lidOpenR = openLid;
}

// Process Left Swapper commands
void SwapperLeft(int8_t arm, int8_t lid) {
  // Lid Open/Close
  if (lid < 50 && lidOpenL) {  // Currently Open - Close
    MoveLeftLid(false);
  } else if (lid > 50 && !lidOpenL) {  // Currently Closed - Open
    MoveLeftLid(true);
  }

  // Arm Process
  arm *= -1;  // reverse for left arm
  uint8_t armAngle = map(arm, -100, 100, angleRev, angleFwd);
  ServoProcess(PWM_CHANNEL_ARM_L, constrain(armAngle + armTrimLeft, 0, 180));
  // ServoProcess(armServo, armAngle, PP_ARM_LEFT, 75);
}

// Process Right Swapper commands
void SwapperRight(int8_t arm, int8_t lid) {
  // Lid Open/Close
  if (lid < 50 && lidOpenR) {  // Currently Open - Close
    MoveRightLid(false);
  } else if (lid > 50 && !lidOpenR) {  // Currently Closed - Open
    MoveRightLid(true);
  }

  // Arm Process
  uint8_t armAngle = map(arm, -100, 100, angleRev, angleFwd);
  ServoProcess(PWM_CHANNEL_ARM_R, constrain(armAngle + armTrimRight, 0, 180));
  // ServoProcess(armServo, armAngle, PP_ARM_RIGHT, 75);
}

// Process swapper control signals
void SwapperProcess(int8_t select, int8_t arm, int8_t lid, int8_t airFilter) {
  if (select < -50) {
    selectDetect = false;
    if (lidOpenR) MoveRightLid(false);
    if (lidOpenL) MoveLeftLid(false);
    if (filterActive) AirFilter(false);
    return;
  }

  if (!selectDetect) {
    selectDetect = true;
    return;
  }

  // Airfilter
  if (airFilter > 50) {
    AirFilter(true);
  } else {
    AirFilter(false);
  }

  // Left
  if (select > 50) {
    SwapperLeft(arm, lid);
  }
  // Right
  else {
    SwapperRight(arm, lid);
  }
}

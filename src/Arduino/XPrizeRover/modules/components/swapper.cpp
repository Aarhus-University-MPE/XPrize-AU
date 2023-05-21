/*
  XPrize Rover eDNA swapper

  Mads Rosenhøj Jeppesen
  Aarhus University
  2023
*/

#pragma once

#include "../setup/modules.h"

Servo lidServo, armServo;

bool lidOpenL     = false;
bool lidOpenR     = false;
bool selectDetect = false;

const uint8_t lidOpenPosLeft  = 37;
const uint8_t lidOpenPosRight = 110;

const uint8_t angleRev = 10;
const uint8_t angleFwd = 170;

const int8_t angleResolution = 30;

// Open/Close Left lid
void MoveLeftLid(bool openLid) {
  uint8_t angle = lidOpenPosLeft;
  int8_t angleIncrements;

  if (openLid) {  // Open lid
    angle += 90;
    angleIncrements = -90 / angleResolution;
  } else {  // Close lid
    angleIncrements = 90 / angleResolution;
  }

  for (size_t i = 0; i < angleResolution; i++) {
    angle += angleIncrements;
    ServoProcess(lidServo, angle, PP_LID_LEFT);
  }

  lidOpenL = openLid;
}

// Open/Close Right lid
void MoveRightLid(bool openLid) {
  uint8_t angle = lidOpenPosRight;
  int8_t angleIncrements;

  if (openLid) {  // Open lid
    angle -= 90;
    angleIncrements = 90 / angleResolution;
  } else {  // Close lid
    angleIncrements = -90 / angleResolution;
  }

  for (size_t i = 0; i < angleResolution; i++) {
    angle += angleIncrements;
    ServoProcess(lidServo, angle, PP_LID_RIGHT);
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
  ServoProcess(armServo, armAngle, PP_ARM_LEFT, 75);
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
  ServoProcess(armServo, armAngle, PP_ARM_RIGHT, 75);
}

void SwapperProcess(int8_t select, int8_t arm, int8_t lid) {
  if (select < -50) {
    digitalWrite(PP_ARM_LEFT, true);
    digitalWrite(PP_ARM_RIGHT, true);
    digitalWrite(PP_LID_LEFT, true);
    digitalWrite(PP_LID_RIGHT, true);
    selectDetect = false;
    return;
  }

  if (!selectDetect) {
    selectDetect = true;
    return;
  }

  // Left
  if (select > 50) {
    digitalWrite(PP_ARM_RIGHT, true);
    digitalWrite(PP_LID_RIGHT, true);
    SwapperLeft(arm, lid);
  }
  // Right
  else {
    digitalWrite(PP_ARM_LEFT, true);
    digitalWrite(PP_LID_LEFT, true);
    SwapperRight(arm, lid);
  }
}

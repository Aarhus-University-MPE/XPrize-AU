#line 1 "D:\\Projects\\XPrize-AU\\src\\Arduino\\XPrizeRover\\modules\\components\\imuCom.cpp"
/*
  XPrize Rover IMU Data

  Mads Rosenhøj Jeppesen
  Aarhus University
  2023
*/

#pragma once

#include "../setup/modules.h"

SFE_HMC6343 compass;  // Declare the sensor object

// Initialize IMU
void ImuInitialize() {
  // Start I2C
  Wire.begin();

  if (!compass.init()) {
    DEBUG_PRINTLN("HMC Failed to initialize");  // Report failure, is the sensor wiring correct?
  } else {
    compass.setOrientation(LEVEL);
    delay(1);  // 1 ms before sensor can receive commands after setting orientation
  }
}

void ImutCalibrate() {
  compass.enterCalMode();
  delay(1);
  delay(60000);
  compass.exitCalMode();
  delay(50);
}

// Return latest heading
float ImuHeading() {
  compass.readHeading();
  return compass.heading;
}

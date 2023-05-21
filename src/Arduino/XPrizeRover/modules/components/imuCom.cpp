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
  Wire.setClock(400000);

  if (!compass.init()) {
  } else {
    compass.setOrientation(LEVEL);
    delay(1);  // 1 ms before sensor can receive commands after setting orientation
  }
}

void ImuUpdate() {
  compass.readHeading();
}

// Return latest heading
float ImuHeading() {
  float heading = (float)(compass.heading) / 10.0f;

  // Rotate 90 degrees
  if (heading + 90 > 360) {
    heading -= 270;
  } else {
    heading += 90;
  }
  return heading;
}

float ImuPitch() {
  return (float)(compass.roll) / 10.0f;
}
float ImuRoll() {
  return (float)(compass.pitch) / 10.0f;
}

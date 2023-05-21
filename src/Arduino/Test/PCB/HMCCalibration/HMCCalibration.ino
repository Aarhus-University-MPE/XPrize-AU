/******************************************************************************
HMC6343_basics.ino
Simple example for using the HMC6343 3-axis compass library.
Jordan McConnell @ SparkFun Electronics
17 July 2014
https://github.com/sparkfun/SparkFun_HMC6343_Arduino_Library

This example declares an SFE_HMC6343 object called compass. The object/sensor
is initialized and if the initialization fails, the sensor could not
be found and read from successfully.

Each time through the loop, heading values (heading, pitch, and roll) and
accelerometer values (accelX, accelY, accelZ) are read from the sensor. They
are then printed to the Serial Monitor at 115200 baud. The raw sensor values
are printed as well as scaled values in readable units (degrees and g forces).

The HMC6343 breakout board needs to be powered with 3.3V and uses I2C to talk
to the microcontroller. If you're using a 5V microcontroller board, such as
the standard Arduino UNO, you'll need a Logic Level Converter for the I2C lines,
such as SparkFun's BOB-12009.

Developed/Tested with:
Arduino Uno
Arduino IDE 1.0.5 & 1.5.2

Requires:
SFE_HMC6343_Library

This code is beerware.
Distributed as-is; no warranty is given.
******************************************************************************/

// Libraries for I2C and the HMC6343 sensor
#include <Wire.h>

#include "SFE_HMC6343.h"

SFE_HMC6343 compass;  // Declare the sensor object

bool active = false;

void setup() {
  pinMode(A7, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, false);
  pinMode(4, OUTPUT);
}

void Init() {
  digitalWrite(4, true);

  // Give the HMC6343 a half second to wake up
  delay(500);

  // Start I2C
  Wire.begin();

  // Initialize the HMC6343 and verify its physical presence
  if (!compass.init()) {
  } else {
    compass.setOrientation(LEVEL);
    compass.enterCalMode();
    delay(1);
    digitalWrite(LED_BUILTIN, true);
    delay(120000);
    compass.exitCalMode();
    delay(50);
    digitalWrite(LED_BUILTIN, false);
  }
}

void loop() {
  if (analogRead(A7) > 800) {
    if (!active) {
      Init();
      active = true;
    }
  } else {
    digitalWrite(LED_BUILTIN, false);
    digitalWrite(4, false);
  }
}

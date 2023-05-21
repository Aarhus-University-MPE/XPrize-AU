#pragma once

#include <Arduino.h>
#include <SBUS.h>
// #include <SD.h>
#include <SFE_HMC6343.h>
// #include <SPI.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <Sparkfun_u-blox_Barebone_I2C_Pos.h>
#include <Wire.h>
#include <mavlink.h>

// Config
#include "../../config/constants.h"
#include "../../config/pinout.h"

// Function prototypes
#include "./prototypes.h"

// System Control
#include "../system/control.cpp"
#include "../system/power.cpp"

// Components
#include "../components/driveTrain.cpp"
#include "../components/gnss.cpp"
#include "../components/imuCom.cpp"
#include "../components/pinconfigs.cpp"
#include "../components/sbusCom.cpp"
// #include "../components/sdReader.cpp"
#include "../components/servoDriver.cpp"
#include "../components/swapper.cpp"
#include "../components/telemetry.cpp"

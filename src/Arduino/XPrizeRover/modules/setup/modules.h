#pragma once

#include <Arduino.h>
#include <EEPROM.h>
#include <SBUS.h>
#include <SD.h>
#include <SFE_HMC6343.h>
#include <SPI.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <TimeLib.h>
#include <Wire.h>
#include <mavlink.h>

// Config
#include "../../config/constants.h"
#include "../../config/memory.h"
#include "../../config/pinout.h"

// Function prototypes
#include "./prototypes.h"

// Helper functions
#include "../tools/generalFunctions.h"

// Initial modules
#include "./pinconfigs.h"

// System Control
#include "../system/control.h"
#include "../system/logging.h"
#include "../system/power.h"

// Communication

// Debug
#include "../debug/debug.h"

// Components
#include "../components/datarecorder.h"
#include "../components/motor.h"
#include "../components/sdReader.h"

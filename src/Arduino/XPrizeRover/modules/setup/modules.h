#pragma once

#include <Arduino.h>
#include <EEPROM.h>
#include <SD.h>
#include <SPI.h>
#include <Servo.h>
#include <TimeLib.h>
#include <Wire.h>

// Config
#include "../../config/commandlist.h"
#include "../../config/components.h"
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
#include "../system/blackbox.h"
#include "../system/control.h"
#include "../system/heartbeat.h"
#include "../system/logging.h"
#include "../system/power.h"

// Communication
#include "../communication/usb.h"

// Debug
#include "../debug/debug.h"

// Components
#include "../components/datarecorder.h"
#include "../components/motor.h"
#include "../components/sdReader.h"

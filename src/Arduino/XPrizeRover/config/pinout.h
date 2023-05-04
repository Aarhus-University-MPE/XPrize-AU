/*
  Lake Profiler system pinout

  Naming pattern (all uppercase):
  P   + <I:input, T: interrupt input, A:analog input, O:output, P:pwm output>_
    + <general part name>_
    + <purpose>_
    + <where applicable: left, right, top, bottom, position etc...>

  Mads Rosenhøj Jepepsen
  Aarhus University
  2021
*/

#pragma once

#include "../modules/setup/modules.h"

// Battery Reading
#define PA_SENSOR_BATT  A6

// Outputs
#define PO_AIRFILTER_EN A0
#define PO_SYSTEN_EN    4
#define PO_HEADLIGHT_EN 5

// PWM Signals
#define PP_ARM_RIGHT    A1
#define PP_ARM_LEFT     A2
#define PP_THROTTLE     A3
#define PP_STEER        6
#define PP_GEAR         7
#define PP_LID_LEFT     8
#define PP_LID_RIGHT    9

// Communication
#define PI_TELEM_TX     2
#define PI_TELEM_RX     3
#define PO_SPISS_SDCARD 10  // 12 MISO, 11 MOSI, 13 SCK
#define COM_SBUS        Serial
// GPS & IMU Connection                 I2C A2 SCL, A4 SDA

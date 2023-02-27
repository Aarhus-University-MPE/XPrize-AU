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
#define PA_SENSOR_BATT       A0

// Servo Motors
#define PO_MOTOR_ARM_LEFT    3
// #define PO_MOTOR_ARM_RIGHT   3
#define PO_MOTOR_LATCH_LEFT  4
#define PO_MOTOR_LATCH_RIGHT 5

// Communication
#define PO_SPISS_SDCARD      53  // 50 MISO, 51 MOSI, 52 SCK
// RTC Connection                 I2C SCL, SDA

#define COM_SERIAL_DBG       Serial

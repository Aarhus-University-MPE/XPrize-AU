/*
  XPrize Rover system pinout

  Naming pattern (all uppercase):
  P   + <I:input, T: interrupt input, A:analog input, O:output, P:pwm output>_
    + <general part name>_
    + <purpose>_
    + <where applicable: left, right, top, bottom, position etc...>

  Mads Rosenhøj Jeppesen
  Aarhus University
  2023
*/

#pragma once

#include "../modules/setup/modules.h"

// Battery Reading
#define PA_SENSOR_BATT       A6
#define PI_POWER_FLAG        A7

// Outputs
#define PO_AIRFILTER_EN      A0
#define PO_SYSTEM_EN         4
#define PO_HEADLIGHT_EN      5

// PWM Signals
#define PP_ARM_RIGHT         A1
#define PP_ARM_LEFT          A2
#define PP_THROTTLE          A3
#define PP_STEER             6
#define PP_GEAR              7
#define PP_LID_LEFT          8
#define PP_LID_RIGHT         9

// PWM Channels
#define PWM_CHANNEL_ARM_R    0
#define PWM_CHANNEL_ARM_L    1
#define PWM_CHANNEL_LID_L    2
#define PWM_CHANNEL_LID_R    3
#define PWM_CHANNEL_GEAR     4
#define PWM_CHANNEL_STEER_L  5
#define PWM_CHANNEL_STEER_R  6
#define PWM_CHANNEL_THROTTLE 7

// Communication
#define PT_TELEM_TX          2
#define PR_TELEM_RX          3
#define PO_SPISS_SDCARD      10  // 12 MISO, 11 MOSI, 13 SCK
#define COM_SBUS             Serial
#define COM_SERIAL_DBG       Serial

// GPS & IMU Connection                 I2C A2 SCL, A4 SDA

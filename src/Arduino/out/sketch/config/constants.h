#line 1 "D:\\Projects\\XPrize-AU\\src\\Arduino\\XPrizeRover\\config\\constants.h"
/*
  XPrize Rover system constants

  Mads Rosenhøj Jeppesen
  Aarhus University
  2023
*/

#pragma once

#include "../modules/setup/modules.h"

// ------------------------------------------------------------ //
//                            DEBUG                             //
// ------------------------------------------------------------ //

// Debug configuration flag - Comment out to unset
// #define DEBUG_BLACKBOX_AND_PRINT
// #define DEBUG_BLACKBOX
// #define DEBUG_SERIAL
#define DEBUG_NONE

// Executes if DEBUG flag is set.
#if defined(DEBUG_BLACKBOX_AND_PRINT)
#define DBG_ONLY(x) x
#define DEBUG_PRINT(x) \
  BlackBoxAppend(x);   \
  Serial.print(x)
#define DEBUG_PRINT2(x, y) \
  BlackBoxAppend(x, y);    \
  Serial.print(x, y)
#define DEBUG_PRINTLN(x) \
  BlackBoxAppendln(x);   \
  Serial.println(x)
#define DEBUG_PRINTLN2(x, y) \
  BlackBoxAppendln(x, y);    \
  Serial.println(x, y)
#define DEBUG_PRINTLINE() \
  Serial.println(F("------------------------------------"))
#define DEBUG_WRITE(x) Serial.write(x)
#define RECEIVE_CMDS() recvWithStartEndMarkers()
#endif

#if defined(DEBUG_BLACKBOX)
#define DBG_ONLY(x)
#define DEBUG_PRINT(x)       BlackBoxAppend(x)
#define DEBUG_PRINT2(x, y)   BlackBoxAppend(x, y)
#define DEBUG_PRINTLN(x)     BlackBoxAppendln(x)
#define DEBUG_PRINTLN2(x, y) BlackBoxAppendln(x, y)
#define DEBUG_PRINTLINE()
#define DEBUG_WRITE(x)
#define RECEIVE_CMDS()
#endif

#if defined(DEBUG_SERIAL)
#define DBG_ONLY(x)          x
#define DEBUG_PRINT(x)       Serial.print(x)
#define DEBUG_PRINT2(x, y)   Serial.print(x, y)
#define DEBUG_PRINTLN(x)     Serial.println(x)
#define DEBUG_PRINTLN2(x, y) Serial.println(x, y)
#define DEBUG_PRINTLINE()    Serial.println(F("------------------------------------"))
#define DEBUG_WRITE(x)       Serial.write(x)
#define RECEIVE_CMDS()       recvWithStartEndMarkers()
#endif

#if defined(DEBUG_NONE)
#define DBG_ONLY(x)
#define DEBUG_PRINT(x)
#define DEBUG_PRINT2(x, y)
#define DEBUG_PRINTLN(x)
#define DEBUG_PRINTLN2(x, y)
#define DEBUG_PRINTLINE()
#define DEBUG_WRITE(x)
#define RECEIVE_CMDS()
#endif

#define ToBoolString(m)         ((m) == 1 ? "T" : ((m) == 0 ? "F" : "Unknown"))
// ------------------------------------------------------------ //
//                           SYSTEM                             //
// ------------------------------------------------------------ //
#define SystemVersion           "0.0.1"

// ------------------------------------------------------------ //
//                         CONTROLLER                           //
// ------------------------------------------------------------ //

#define SBUS_TIMEOUT            5000  // milliseconds
#define SBUS_PERIOD             100   // milliseconds between SBUS updates
#define POWERFLAG_PERIOD        500   // milliseconds between power flag checks

// Controller Channels
#define CHANNEL_STEER           1  // Right Horizontal
#define CHANNEL_THROTTLE        2  // Left Vertical
#define CHANNEL_SWAPPER_ARM     3  // Right Vertical
#define CHANNEL_SWAPPER_SELECT  5  // A or D Short press, reset with B Short Press
#define CHANNEL_SWAPPER_LID     6  // CAM (Trigger) Short press
#define CHANNEL_GEAR            7  // C Long Press
#define CHANNEL_SLEEP           8  // Home Long Press
#define CHANNEL_HEADLIGHTS      9  // C Short Press

#define SBUS_SIGNAL_HIGH        800

// ------------------------------------------------------------ //
//                           BATTERY                            //
// ------------------------------------------------------------ //

#define BATTERY_VOLTAGE_MIN     16.97f  // Count as 0% when below this voltage
#define BATTERY_VOLTAGE_MAX     18.06f  // Count as 100% when above this voltage

// ------------------------------------------------------------ //
//                        COMMUNICATION                         //
// ------------------------------------------------------------ //

// DEBUG
#define DEBUG_BAUDRATE          115200

// Mavlink
#define MAVLINK_BAUDRATE        115200

#define MAVLINK_PERIOD_GNSS     3000
#define MAVLINK_PERIOD_GNSSDATA 3000
#define MAVLINK_PERIOD_HRTBEAT  1000
#define MAVLINK_PERIOD_BATTERY  2000
#define MAVLINK_PERIOD_HEADING  3000

// Comment to disable MAVLink messages
#define MAV_HEARTBEAT           1
#define MAV_BATTERY             1
#define MAV_GNSS                1
#define MAV_GNSSDATA            1
#define MAV_HEADING             1
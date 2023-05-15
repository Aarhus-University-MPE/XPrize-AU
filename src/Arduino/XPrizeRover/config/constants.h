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
#define SystemVersion           "1.0.43"

#define POWERFLAG_PERIOD        500  // milliseconds between power flag checks
#define POWERFLAG_TOGGLE        400  // milliseconds after power flag has been toggled to enable/disable power

#define POWER_DOWN_DURATION     3600    // Seconds powered down after (increments of 9)
#define POWER_WAKE_DURATION     600000  // milliseconds to stay awake after a power down cycle

// ------------------------------------------------------------ //
//                         CONTROLLER                           //
// ------------------------------------------------------------ //

// SBUS
#define SBUS_TIMEOUT            5000  // milliseconds
#define SBUS_PERIOD             100   // milliseconds between SBUS updates

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

// #define BATTERY_TYPE_NIMH       1
#define BATTERY_TYPE_LIPO       1

// ------------------------------------------------------------ //
//                        COMMUNICATION                         //
// ------------------------------------------------------------ //

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

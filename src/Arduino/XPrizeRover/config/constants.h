/*
  XPrize Rover system constants

  Mads Rosenhøj Jeppesen
  Aarhus University
  2023
*/

#pragma once

#include "../modules/setup/modules.h"

// ------------------------------------------------------------ //
//                           SYSTEM                             //
// ------------------------------------------------------------ //
#define SystemVersion           "1.0.96"

#define POWERFLAG_PERIOD        500  // milliseconds between power flag checks

#define POWER_DOWN_DURATION     3600    // Seconds powered down after (increments of 9)
#define POWER_WAKE_DURATION     600000  // milliseconds to stay awake after a power down cycle

// ------------------------------------------------------------ //
//                         CONTROLLER                           //
// ------------------------------------------------------------ //

// SBUS
#define SBUS_TIMEOUT            5000  // milliseconds
#define SBUS_PERIOD             50    // milliseconds between SBUS updates

// Controller Channels
#define CHANNEL_STEER           1  // Right Horizontal
#define CHANNEL_THROTTLE        2  // Left Vertical
#define CHANNEL_SWAPPER_ARM     3  // Right Vertical
#define CHANNEL_SWAPPER_SELECT  5  // A or D Short press, reset with B Short Press
#define CHANNEL_SWAPPER_LID     6  // CAM (Trigger) Short press
#define CHANNEL_GEAR            7  // C Long Press
#define CHANNEL_SLEEP           8  // Home Long Press
#define CHANNEL_HEADLIGHTS      9  // C Short Press

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
#define MAVLINK_PERIOD_HRTBEAT  2000
#define MAVLINK_PERIOD_BATTERY  2000
#define MAVLINK_PERIOD_HEADING  3000

// Comment to disable MAVLink messages
#define MAV_HEARTBEAT           1
#define MAV_BATTERY             1
#define MAV_GNSS                1
#define MAV_GNSSDATA            1
#define MAV_HEADING             1

/*
  Lake Profiler system constants

  Mads Rosenhøj Jepepsen
  Aarhus University
  2021
*/

#pragma once

#include "../modules/setup/modules.h"

// ------------------------------------------------------------ //
//                            DEBUG                             //
// ------------------------------------------------------------ //

// Debug configuration flag - Comment out to unset
#define DEBUG_BLACKBOX_AND_PRINT
// #define DEBUG_BLACKBOX
// #define DEBUG_SERIAL
// #define DEBUG_NONE

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

#define ToBoolString(m)       ((m) == 1 ? "T" : ((m) == 0 ? "F" : "Unknown"))
// ------------------------------------------------------------ //
//                           SYSTEM                             //
// ------------------------------------------------------------ //
#define SystemVersion         "0.0.1"

// ------------------------------------------------------------ //
//                            MOTOR                             //
// ------------------------------------------------------------ //

#define MOTOR_LEFT_ARM        0  //
#define MOTOR_RIGHT_ARM       1  //
#define MOTOR_LEFT_LATCH      2  //
#define MOTOR_RIGHT_LATCH     3  //

// ------------------------------------------------------------ //
//                           BATTERY                            //
// ------------------------------------------------------------ //

#define BATTERY_MIN_LEVEL     50

#define BATTERY_VOLTAGE_MIN   10.7f
#define BATTERY_VOLTAGE_MAX   12.6f

// ------------------------------------------------------------ //
//                        COMMUNICATION                         //
// ------------------------------------------------------------ //

// Buttons
#define BTN_DEBOUNCE_TIME     500
#define ESTOP_DEBOUNCE_TIME   1000

// DEBUG
#define DEBUG_BAUDRATE        115200

// Canister Comm (RS232)
#define CANISTER_BAUDRATE     19200
#define LOGGING_START_TIMEOUT 3000000

// LORA
#define COM_LORA_BAUDRATE     9600
#define LORA_FREQUENCY        434.0
#define CLIENT_ADDRESS        1
#define SERVER_ADDRESS        2
#define MAX_LORA_BROADCAST    10
#define LORA_BROADCAST_DELAY  5000
#define LORA_HEARTBEAT_PERIOD 900000L  // 15 min
#define LORA_ACTIVE           true
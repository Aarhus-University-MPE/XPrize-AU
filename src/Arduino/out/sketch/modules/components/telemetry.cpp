#line 1 "D:\\Projects\\XPrize-AU\\src\\Arduino\\XPrizeRover\\modules\\components\\telemetry.cpp"
/*
  XPrize Rover Telemetry, broadcast data to controller

  Mads Rosenhøj Jeppesen
  Aarhus University
  2023
*/

#pragma once

#include "../setup/modules.h"

SoftwareSerial SerialMAV(PR_TELEM_RX, PT_TELEM_TX);

unsigned long millisMavGnss, millisMavGnssData, millisMavHeartbeat, millisMavBattery, millisMavHeading;

// MAVLink config
const uint8_t sysid          = 1;  ///< ID 20 for this airplane. 1 PX, 255 ground station
const uint8_t compid         = 1;  ///< The component sending the message
const uint8_t type           = MAV_TYPE_GROUND_ROVER;
const uint8_t system_type    = MAV_TYPE_GENERIC;
const uint8_t autopilot_type = MAV_AUTOPILOT_INVALID;
uint8_t system_mode          = MAV_MODE_MANUAL_ARMED;
uint8_t system_state         = MAV_STATE_STANDBY;

// Initialize Telemetry Communication
void TelemetryInitialize() {
  SerialMAV.begin(MAVLINK_BAUDRATE);
}

// Terminate Telemetry Communication
void TelemetryTerminate() {
  SerialMAV.end();
}

// Broadcast mavlink message
void sendMsg(mavlink_message_t* msg) {
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];

  // Copy message to send buffer
  uint16_t len = mavlink_msg_to_send_buffer(buf, msg);

  // Send message
  SerialMAV.write(buf, len);  // Write command to Telem Port
}

// Broadcast Standard Heartbeat
void MavHeartbeat() {
  if (millis() - millisMavHeartbeat < MAVLINK_PERIOD_HRTBEAT) return;
  millisMavHeartbeat = millis();
  mavlink_message_t msg;

  // Bundle and send data
  mavlink_msg_heartbeat_pack(sysid, compid, &msg, type, autopilot_type, system_mode, 0, system_state);
  sendMsg(&msg);
}

// Broadcast Battery Data
void MavBattery() {
  if (millis() - millisMavBattery < MAVLINK_PERIOD_BATTERY) return;
  millisMavBattery = millis();
  mavlink_message_t msg;

  // Acquire battery data
  int16_t voltage     = BatteryVoltageInt();
  int16_t currentDraw = -1;  // Not measured
  int8_t batteryLevel = BatteryLevel();

  // Bundle and send data
  mavlink_msg_sys_status_pack(sysid, compid, &msg, 0, 0, 0, 0, voltage, currentDraw, batteryLevel, 0, 0, 0, 0, 0, 0);
  sendMsg(&msg);
}

// Broadcast GNSS Data (Position)
void MavGnss() {
  if (millis() - millisMavGnss < MAVLINK_PERIOD_GNSS) return;
  millisMavGnss = millis();
  mavlink_message_t msg;

  // Acquire GNSS position data
  int32_t lat = GnssGetLat();   // 1E7 degrees
  int32_t lon = GnssGetLong();  // 1E7 degrees

  // Broadcast GNSS positional data
  mavlink_msg_global_position_int_pack(sysid, compid, &msg, millis(), lat, lon, 0, 0, 0, 0, 0, 0);
  sendMsg(&msg);
}

// Broadcast GNSS Data (Satellite, fixtype)
void MavGnssData() {
  if (millis() - millisMavGnssData < MAVLINK_PERIOD_GNSSDATA) return;

  millisMavGnssData = millis();
  mavlink_message_t msg;

  // Acquire GNSS Data
  uint8_t fix_type           = GnssGetFixType();  // 0-1: no fix, 2: 2D, 3: 3D fix
  uint8_t satellites_visible = GnssGetSIV();

  // Broadcast GNSS signal data
  mavlink_msg_gps_raw_int_pack(sysid, compid, &msg, 0, fix_type, 0, 0, 0, 65535, 65535, 0, 65535, satellites_visible);
  sendMsg(&msg);
}

// Broadcast Heading Data
void MavHeading() {
  if (millis() - millisMavHeading < MAVLINK_PERIOD_HEADING) return;
  millisMavHeading = millis();
  mavlink_message_t msg;

  // Acquire heading data
  // float heading = ImuHeading(); // TODO: Reimplement
  float heading = GnssGetHeading();

  // Broadcast IMU signal data
  mavlink_msg_attitude_pack(sysid, compid, &msg, millis(), 0.0f, 0.0f, DEG_TO_RAD * heading, 0, 0, 0);
  sendMsg(&msg);
}

// Process Telemetry Communication
void TelemetryProcess() {
#ifdef MAV_HEARTBEAT
  MavHeartbeat();
#endif
#ifdef MAV_BATTERY
  MavBattery();
#endif
#ifdef MAV_GNSS
  MavGnss();
#endif
#ifdef MAV_GNSSDATA
  MavGnssData();
#endif
#ifdef MAV_HEADING
  MavHeading();
#endif
}

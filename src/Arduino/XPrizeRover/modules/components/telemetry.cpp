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

mavlink_message_t msg;

// Initialize Telemetry Communication
void TelemetryInitialize() {
  SerialMAV.begin(MAVLINK_BAUDRATE);
}

// Terminate Telemetry Communication
void TelemetryTerminate() {
  SerialMAV.end();
}

uint8_t buf[MAVLINK_MAX_PACKET_LEN];

// Broadcast mavlink message
void sendMsg(mavlink_message_t* msg) {
  // Copy message to send buffer
  uint16_t len = mavlink_msg_to_send_buffer(buf, msg);

  // Send message
  SerialMAV.write(buf, len);  // Write command to Telem Port
}

// Broadcast Standard Heartbeat
bool MavHeartbeat() {
  if (millis() - millisMavHeartbeat < MAVLINK_PERIOD_HRTBEAT) return false;
  millisMavHeartbeat = millis();

  // Bundle and send data
  mavlink_msg_heartbeat_pack(sysid, compid, &msg, type, autopilot_type, system_mode, 0, system_state);
  sendMsg(&msg);
  return true;
}

// Broadcast Battery Data
bool MavBattery() {
  if (millis() - millisMavBattery < MAVLINK_PERIOD_BATTERY) return false;
  millisMavBattery = millis();

  // Acquire battery data
  int16_t voltage     = BatteryVoltageInt();
  int16_t currentDraw = -1;  // Not measured
  int8_t batteryLevel = BatteryLevel();

  // Bundle and send data
  mavlink_msg_sys_status_pack(sysid, compid, &msg, 0, 0, 0, 0, voltage, currentDraw, batteryLevel, 0, 0, 0, 0, 0, 0);
  sendMsg(&msg);
  return true;
}

// Broadcast GNSS Data (Position)
bool MavGnss() {
  if (millis() - millisMavGnss < MAVLINK_PERIOD_GNSS) return false;
  millisMavGnss = millis();

  // Acquire GNSS position data
  GnssUpdate();
  int32_t lat = GnssGetLat();   // 1E7 degrees
  int32_t lon = GnssGetLong();  // 1E7 degrees

  // Broadcast GNSS positional data
  mavlink_msg_global_position_int_pack(sysid, compid, &msg, millis(), lat, lon, 0, 0, 0, 0, 0, 0);
  sendMsg(&msg);
  return true;
}

// Broadcast GNSS Data (Satellite, fixtype)
bool MavGnssData() {
  if (millis() - millisMavGnssData < MAVLINK_PERIOD_GNSSDATA) return false;

  millisMavGnssData = millis();

  // Acquire GNSS Data
  uint8_t fix_type           = GnssGetFixType();  // 0-1: no fix, 2: 2D, 3: 3D fix
  uint8_t satellites_visible = GnssGetSIV();

  int32_t lat = GnssGetLat();   // 1E7 degrees
  int32_t lon = GnssGetLong();  // 1E7 degrees
  uint16_t eph;                 ///< GPS HDOP horizontal dilution of position in cm (m*100). If unknown, set to: 65535

  // Broadcast GNSS signal data
  mavlink_msg_gps_raw_int_pack(sysid, compid, &msg, 0, fix_type, lat, lon, 0, eph, 65535, 0, 65535, satellites_visible);
  sendMsg(&msg);
  return true;
}

// Broadcast Heading Data
bool MavHeading() {
  if (millis() - millisMavHeading < MAVLINK_PERIOD_HEADING) return false;
  millisMavHeading = millis();

  // Acquire heading data
  ImuUpdate();
  // float heading = ImuHeading();
  float pitch   = ImuPitch();
  float roll    = ImuRoll();
  float heading = GnssGetHeading();

  // Broadcast IMU signal data
  mavlink_msg_attitude_pack(sysid, compid, &msg, millis(), DEG_TO_RAD * roll, DEG_TO_RAD * pitch, DEG_TO_RAD * heading, 0, 0, 0);
  sendMsg(&msg);
  return true;
}

// Process Telemetry Communication
void TelemetryProcess() {
#ifdef MAV_HEARTBEAT
  if (MavHeartbeat()) return;
#endif
#ifdef MAV_BATTERY
  if (MavBattery()) return;
#endif
#ifdef MAV_GNSS
  if (MavGnss()) return;
#endif
#ifdef MAV_GNSSDATA
  if (MavGnssData()) return;
#endif
#ifdef MAV_HEADING
  if (MavHeading()) return;
#endif
}

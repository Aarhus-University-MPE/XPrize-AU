#line 1 "D:\\Projects\\XPrize-AU\\src\\Arduino\\XPrizeRover\\modules\\components\\gnss.cpp"
/*
  XPrize Rover GNSS communication

  Mads Rosenhøj Jeppesen
  Aarhus University
  2023
*/

#pragma once

#include "../setup/modules.h"

SFE_UBLOX_GNSS gnss;

// Initialize GNSS module
void GnssInitialize() {
  Wire.begin();
  Wire.setClock(400000);
  // Wire.setWireTimeout(1000);
  gnss.begin();
  gnss.setI2COutput(COM_TYPE_UBX);                  // Set the I2C port to output UBX only (turn off NMEA noise)
  gnss.setNavigationFrequency(1);                   // Set output to 5 times a second
  gnss.saveConfigSelective(VAL_CFG_SUBSEC_IOPORT);  // Save (only) the communications port settings to flash and BBR
}

// Gets positional data in Latitude in degrees * 10^-7
int32_t GnssGetLat() {
  return gnss.getLatitude(10);
}

// Gets positional data in int32_titude in degrees * 10^-7
int32_t GnssGetLong() {
  return gnss.getLongitude(10);
}

uint8_t GnssGetSIV() {
  return gnss.getSIV();
}

uint8_t GnssGetFixType() {
  return gnss.getFixType();
}

float GnssGetHeading() {
  // int32_t headingInt = gnss.getHeadVeh();  // x 10^-5
  int32_t headingInt = gnss.getHeading();  // x 10^-5

  float heading = headingInt / 100000.0f;
  return heading;
}
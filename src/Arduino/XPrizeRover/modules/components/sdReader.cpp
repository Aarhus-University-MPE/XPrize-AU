/*
  XPrize Rover local storage protocols

  Mads Rosenhøj Jeppesen
  Aarhus University
  2023
*/

#pragma once

#include "../setup/modules.h"

// // Initialize SD card reader module.
// void SDReaderInitialize() {
//   if (SD.begin(PO_SPISS_SDCARD)) {
//     File dataFile = SD.open("GPS.txt", FILE_WRITE);
//     dataFile.close();
//   }
// }

// void SaveGNSS() {
//   File dataFile = SD.open("GPS.txt", FILE_WRITE);
//   dataFile.print(F("Test Data"));
//   dataFile.close();
// }
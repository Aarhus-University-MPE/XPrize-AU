/*
  XPrize Rover EEPROM memory allocation

  Mads Rosenhøj Jeppesen
  Aarhus University
  2023
*/

#pragma once

// Read/Write functions
#define EEPROM_READ_INT(addr)               (int)(((EEPROM.read(addr) << 0) & 0xFF) + ((EEPROM.read(addr + 1) << 8) & 0xFF00))
#define EEPROM_READ_UINT(addr)              (unsigned int)(((EEPROM.read(addr) << 0) & 0xFF) + ((EEPROM.read(addr + 1) << 8) & 0xFF00))

#define EEPROM_READ_ULONG(addr, ulongValue) EEPROM.get(addr, ulongValue)

#define EEPROM_WRITE_UINT(addr, uintValue)  EEPROM.put(addr, uintValue)
#define EEPROM_WRITE_INT(addr, intValue)    EEPROM.put(addr, intValue)

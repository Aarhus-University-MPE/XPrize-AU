#pragma once

#include "../setup/modules.h"

/*
    USB communication, handles reading serial and parsing commands.

    By
    Mads Rosenhoej Jeppesen - Aarhus 2021
    mrj@mpe.au.dk

    Query data from Drill Logger SD card
*/

char receivedCMD[numChars];

bool InitializeDebugComm() {
  COM_SERIAL_DBG.begin(DEBUG_BAUDRATE);

  if (COM_SERIAL_DBG) {
    DEBUG_PRINTLN(F("#--------------------------------#"));
    DEBUG_PRINTLN(F("#     XPrize-Rover Firmware      #"));
    DBG_ONLY(DEBUG_PRINTLN(F("#          #DEBUG MODE#          #")));
    DEBUG_PRINT(F("#      System Version: "));
    DEBUG_PRINT(SystemVersion);
    DEBUG_PRINTLN(F("   #"));
    DEBUG_PRINTLN(F("#--------------------------------#"));
    DEBUG_PRINTLN();
  }

  return COM_SERIAL_DBG;
}

// Receive Commands
void recvWithStartEndMarkers() {
  static boolean recvInProgress = false;
  static byte ndx               = 0;
  char startMarker              = '<';
  char endMarker                = '>';
  char rc;

  while (COM_SERIAL_DBG.available() > 0) {
    rc = COM_SERIAL_DBG.read();

    if (recvInProgress == true) {
      if (rc != endMarker) {
        receivedCMD[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      } else {
        receivedCMD[ndx] = '\0';  // terminate the string
        recvInProgress   = false;
        ndx              = 0;
        parseCommand();
      }
    }

    else if (rc == startMarker) {
      recvInProgress = true;
    }
  }
}

bool DebugCommStatus() {
  return COM_SERIAL_DBG;
}

// Parse read Command
void parseCommand() {
  DEBUG_PRINTLINE();
  DEBUG_PRINT(F("Received command (DBG_PRT): \""));
  DEBUG_PRINT(receivedCMD);
  DEBUG_PRINTLN(F("\""));

  switch (receivedCMD[0]) {
    case CMD_FILES:
      parseCommandFiles();
      break;
    case CMD_POWER:
      parseCommandPower();
      break;
    case CMD_LOGGING:
      parseCommandLogging();
      break;
    case CMD_SAMPLE:
      parseCommandSample();
      break;
    case CMD_MOTOR:
      parseCommandMotor();
      break;
    case '\0':
      break;
    default:
      DEBUG_PRINTLN(F("NACK"));
      break;
  }
}

void parseCommandFiles() {
  char *fileNamePtr       = receivedCMD + 2;
  char fileName[numChars] = {0};
  strcpy(fileName, fileNamePtr);

  switch (receivedCMD[1]) {
    case CMD_FILES_LIST:
      SDQuery();
      break;
    case CMD_FILES_SIZE:
      SDSize(fileName);
      break;
    case CMD_FILES_DOWNLOAD:
      SDDownload(fileName);
      break;
    case CMD_FILES_CREATE:
      SDCreate(fileName);
      break;
    case CMD_FILES_REMOVE:
      SDDelete(fileName);
      break;
    case CMD_FILES_WRITE:
      SDWriteStream(fileName);
      break;
    case CMD_FILES_WRITENEWLINE:
      SDWriteStreamNewLine();
      break;
    case CMD_FILES_QUIT:
      SDQuit();
      break;
    case CMD_FILES_BLCKBOX:
      BlackBoxPrint();
      break;
    case CMD_FILES_BLCKBOXEMPTY:
      BlackBoxEmpty();
      break;
    case '\0':
      break;
    default:
      DEBUG_PRINTLN(F("NACK"));
      break;
  }
}

void parseCommandPower() {
  char *levelPtr           = receivedCMD + 2;
  char levelChar[numChars] = {0};
  strcpy(levelChar, levelPtr);

  int batteryLevel = atoi(levelChar);

  switch (receivedCMD[1]) {
    case CMD_POWER_SET:
      SetBatteryMinLevel(batteryLevel);
      break;
    case CMD_POWER_GET:
      DEBUG_PRINT(F("Minimum Battery Level: "));
      DEBUG_PRINT(GetBatteryMinLevel());
      DEBUG_PRINTLN(F(" %"));
      break;
    case CMD_POWER_PRINT:
      BatteryStatus(true);
      break;
    default:
      break;
  }
}

void parseCommandLogging() {
  switch (receivedCMD[1]) {
    case CMD_LOGGING_START:
      DEBUG_PRINTLN(F("Manual Log Start"));
      break;
    default:
      break;
  }
}

void parseCommandSample() {
  char *idPtr           = receivedCMD + 2;
  char idChar[numChars] = {0};
  strcpy(idChar, idPtr);

  int idInt = atoi(idChar);

  switch (receivedCMD[1]) {
    case CMD_SAMPLE_IDGET:
      DEBUG_PRINT(F("Sample ID: "));
      DEBUG_PRINTLN((int)GetSampleID());
      break;
    case CMD_SAMPLE_IDSET:
      SetSampleID((unsigned int)idInt);
      break;
    default:
      break;
  }
}

void parseCommandMotor() {
  switch (receivedCMD[1]) {
    case CMD_MOTOR_ARM_LEFT:
      DEBUG_PRINTLN(F("Moving Left Arm"));
      MotorMove(Motor::Left_Arm);
      break;
    case CMD_MOTOR_ARM_RIGHT:
      DEBUG_PRINTLN(F("Moving Right Arm"));
      MotorMove(Motor::Right_Arm);
      break;
    case CMD_MOTOR_LATCH_LEFT:
      DEBUG_PRINTLN(F("Moving Left Latch"));
      MotorMove(Motor::Left_Latch);
      break;
    case CMD_MOTOR_LATCH_RIGHT:
      DEBUG_PRINTLN(F("Moving Right Latch"));
      MotorMove(Motor::Right_Latch);
      break;
    default:
      break;
  }
}

void CountDownPrint() {
  DEBUG_PRINT(F("3"));
  delay(333);
  DEBUG_PRINT(F("."));
  delay(333);
  DEBUG_PRINT(F(". "));
  delay(333);
  DEBUG_PRINT(F("2"));
  delay(333);
  DEBUG_PRINT(F("."));
  delay(333);
  DEBUG_PRINT(F(". "));
  delay(333);
  DEBUG_PRINT(F("1"));
  delay(333);
  DEBUG_PRINT(F("."));
  delay(333);
  DEBUG_PRINTLN(F(". "));
  delay(333);
}
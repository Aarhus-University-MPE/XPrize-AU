#pragma once

#include "../setup/modules.h"

// Sets pinmode of all pins and writes initial values for outputs
void InitAllPins() {
  pinMode(PI_POWER_FLAG, INPUT);
  pinMode(PA_SENSOR_BATT, INPUT);

  digitalWrite(PO_AIRFILTER_EN, false);
  digitalWrite(PO_HEADLIGHT_EN, false);
  digitalWrite(PO_SYSTEM_EN, false);

  pinMode(PO_AIRFILTER_EN, OUTPUT);
  pinMode(PO_HEADLIGHT_EN, OUTPUT);
  pinMode(PO_SYSTEM_EN, OUTPUT);

  digitalWrite(PP_ARM_RIGHT, true);
  digitalWrite(PP_ARM_LEFT, true);
  digitalWrite(PP_THROTTLE, false);
  digitalWrite(PP_STEER, false);
  digitalWrite(PP_GEAR, false);
  digitalWrite(PP_LID_LEFT, false);
  digitalWrite(PP_LID_RIGHT, false);

  pinMode(PP_ARM_RIGHT, OUTPUT);
  pinMode(PP_ARM_LEFT, OUTPUT);
  pinMode(PP_THROTTLE, OUTPUT);
  pinMode(PP_STEER, OUTPUT);
  pinMode(PP_GEAR, OUTPUT);
  pinMode(PP_LID_LEFT, OUTPUT);
  pinMode(PP_LID_RIGHT, OUTPUT);
}

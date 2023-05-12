#line 1 "D:\\Projects\\XPrize-AU\\src\\Arduino\\XPrizeRover\\modules\\components\\pinconfigs.cpp"
#pragma once

#include "../setup/modules.h"

// Sets pinmode of all pins and writes initial values for outputs
void InitAllPins() {
  pinMode(PI_POWER_FLAG, INPUT);
  pinMode(PA_SENSOR_BATT, INPUT);

  pinMode(PO_AIRFILTER_EN, OUTPUT);
  pinMode(PO_HEADLIGHT_EN, OUTPUT);
  pinMode(PO_SYSTEM_EN, OUTPUT);

  digitalWrite(PO_AIRFILTER_EN, false);
  digitalWrite(PO_HEADLIGHT_EN, false);
  digitalWrite(PO_SYSTEM_EN, false);
}

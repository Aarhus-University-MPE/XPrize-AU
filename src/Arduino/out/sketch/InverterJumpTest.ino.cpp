#include <Arduino.h>
#line 1 "D:\\Projects\\XPrize-AU\\src\\Arduino\\Test\\InverterJumpTest\\InverterJumpTest.ino"
const int invertPin = A0;

#line 3 "D:\\Projects\\XPrize-AU\\src\\Arduino\\Test\\InverterJumpTest\\InverterJumpTest.ino"
void setup();
#line 7 "D:\\Projects\\XPrize-AU\\src\\Arduino\\Test\\InverterJumpTest\\InverterJumpTest.ino"
void loop();
#line 3 "D:\\Projects\\XPrize-AU\\src\\Arduino\\Test\\InverterJumpTest\\InverterJumpTest.ino"
void setup() {
  pinMode(invertPin, INPUT);
}

void loop() {
  if (digitalRead(invertPin) != digitalRead(LED_BUILTIN)) digitalWrite(LED_BUILTIN, digitalRead(invertPin));
}

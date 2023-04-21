# 1 "D:\\Projects\\XPrize-AU\\src\\Arduino\\Test\\InverterJumpTest\\InverterJumpTest.ino"
const int invertPin = A0;

void setup() {
  pinMode(invertPin, 0x0);
}

void loop() {
  if (digitalRead(invertPin) != digitalRead(13)) digitalWrite(13, digitalRead(invertPin));
}

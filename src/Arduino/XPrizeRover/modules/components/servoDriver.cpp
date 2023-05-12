/*
  XPrize Rover Servo Driver

  Mads Rosenhøj Jeppesen
  Aarhus University
  2023
*/

const uint8_t servoPeriod  = 25;
const uint8_t servoTimeout = 200;

// Process a servo signal for a fixed period
void ServoProcess(Servo &servo, uint8_t angle, int servoPin) {
  servo.attach(servoPin);
  servo.write(angle);

  delay(servoPeriod);
  servo.detach();
}

// Process a servo signal for a fixed period
unsigned long ServoProcess(Servo &servo, uint8_t angle, uint8_t servoPin, uint8_t lastAngle, unsigned long lastMillis) {
  // new signal
  if (angle != lastAngle) {
    servo.attach(servoPin);
    servo.write(angle);
    return millis();
  }

  // Old Signal
  if (millis() - lastMillis > servoTimeout) {
    servo.detach();
  }

  // Serial.begin(115200);
  // Serial.print(angle);
  // Serial.print("\t");
  // Serial.println(lastAngle);
  // Serial.end();
  // SbusInitialize();

  return lastMillis;
}

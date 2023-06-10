/*
  XPrize Rover Servo Driver
  - https://learn.adafruit.com/adafruit-8-channel-pwm-or-servo-featherwing
  - https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library

  Mads Rosenhøj Jeppesen
  Aarhus University
  2023
*/

#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

const uint8_t servoTimeout = 200;

// #define SERVOMIN   41  // 4096/(1s/10) * 1 ms
// #define SERVOMAX   82  // 4096/(1s/10) * 2 ms
// #define SERVO_FREQ 10  // Analog servos run at ~50 Hz updates

#define SERVOMIN   209  // (1000 / 20000 ) * 4096
#define SERVOMAX   410  // (2000 / 20000 ) * 4096
#define SERVO_FREQ 50   // Analog servos run at ~50 Hz updates

// #define SERVOMIN   819   // 4096/(1s/200) * 1 ms
// #define SERVOMAX   1638  // 4096/(1s/200) * 2 ms
// #define SERVO_FREQ 200  // Analog servos run at ~50 Hz updates

// Initialize PWM module
void ServoInitialize() {
  pwm.begin();
  pwm.setOscillatorFrequency(25875000);  // From oscilloscope test
  pwm.setPWMFreq(SERVO_FREQ);            // Analog servos run at ~50 Hz updates
  SwapperInitialize();

  delay(10);
}

void DisableServo(uint8_t channel) {
  // pwm.setPWM(channel, 4096, 0);
}

// Process a servo signal
void ServoProcess(uint8_t channel, uint8_t angle, int8_t extended = 0) {
  uint16_t pulseLen = map(angle, 0, 180, SERVOMIN - extended, SERVOMAX + extended);

  pwm.setPWM(channel, 0, pulseLen);
}

// Process a servo signal for a fixed period
void ServoProcess(Servo &servo, uint8_t angle, int servoPin, uint8_t servoPeriod = 25) {
  servo.attach(servoPin);
  servo.write(angle);

  delay(servoPeriod);
  servo.detach();

  // digitalWrite(servoPin, false);  // TODO: reduce PWM cross bleed?
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

  return lastMillis;
}

// Servo Feather test

#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN         209  // (1000 / 20000 ) * 4096
#define SERVOMAX         410  // (2000 / 20000 ) * 4096

#define SERVO_FREQ       50  // Analog servos run at ~50 Hz updates

#define CHANNEL_GEAR     4
#define CHANNEL_STEER_L  5
#define CHANNEL_STEER_R  6
#define CHANNEL_THROTTLE 7

bool initialized = false;

void ServoInitialize() {
  if (initialized) return;
  pwm.begin();
  pwm.setOscillatorFrequency(25875000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  initialized = true;
  delay(10);

  uint16_t center = map(90, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(CHANNEL_THROTTLE, 0, center);
  pwm.setPWM(CHANNEL_STEER_L, 0, center);
  pwm.setPWM(CHANNEL_STEER_R, 0, center);
}

// Move servo to min and then max
void MoveServo() {
  // digitalWrite(LED_BUILTIN, true);
  // for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
  //   pwm.setPWM(CHANNEL_THROTTLE, 0, pulselen);
  //   delay(100);
  // }

  // delay(2000);
  // pwm.setPWM(CHANNEL_STEER_L, 0, SERVOMAX);
  // pwm.setPWM(CHANNEL_STEER_R, 0, SERVOMAX);
  // delay(2000);
  digitalWrite(LED_BUILTIN, false);
  delay(500);
}

void setup() {
  pinMode(A7, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop() {
  if (analogRead(A7) > 800) {
    digitalWrite(4, true);
    delay(25);
    ServoInitialize();
    // MoveServo();
  } else {
    digitalWrite(LED_BUILTIN, false);
    digitalWrite(4, false);
    initialized = false;
  }
}
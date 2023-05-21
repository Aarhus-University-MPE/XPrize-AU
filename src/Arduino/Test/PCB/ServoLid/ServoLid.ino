// Include the Servo library
#include <Servo.h>

// Outputs
#define PO_AIRFILTER_EN A0
#define PO_SYSTEM_EN    4

// PWM Signals
#define PP_ARM_RIGHT    A1
#define PP_ARM_LEFT     A2
#define PP_LID_LEFT     8
#define PP_LID_RIGHT    9

#define PERIOD          200

#define LID_OPEN_L      34
#define LID_OPEN_R      110

unsigned long lastmillisCycle = 0;

bool active = false;

Servo lidLeft, lidRight, armLeft, armRight;

void setup() {
  pinMode(A7, INPUT);

  digitalWrite(PP_ARM_RIGHT, false);
  digitalWrite(PP_ARM_LEFT, false);
  digitalWrite(PP_LID_LEFT, false);
  digitalWrite(PP_LID_RIGHT, false);

  pinMode(PO_SYSTEM_EN, OUTPUT);
  pinMode(PO_AIRFILTER_EN, OUTPUT);
  pinMode(PP_ARM_RIGHT, OUTPUT);
  pinMode(PP_ARM_LEFT, OUTPUT);
  pinMode(PP_LID_LEFT, OUTPUT);
  pinMode(PP_LID_RIGHT, OUTPUT);
}

void loop() {
  if (millis() - lastmillisCycle < PERIOD) return;

  if (analogRead(A7) > 800) {
    if (!active) {
      digitalWrite(PO_SYSTEM_EN, true);
      digitalWrite(LED_BUILTIN, true);
      active = true;
      delay(1000);
    }

    MoveRightLid(true);
    delay(1000);
    MoveRightLid(false);
    delay(500);
    MoveLeftLid(true);
    delay(1000);
    MoveLeftLid(false);
    delay(500);
  } else {
    digitalWrite(LED_BUILTIN, false);
    digitalWrite(PO_SYSTEM_EN, false);
  }
}

const uint8_t servoPeriod = 25;

// Process a servo signal for a fixed period
void ServoProcess(Servo &servo, uint8_t angle, int servoPin) {
  servo.attach(servoPin);
  servo.write(angle);

  delay(servoPeriod);
  servo.detach();
}

void MoveLeftLid(bool open) {
  uint8_t angle;
  int8_t angleIncrements;
  angle = LID_OPEN_L;

  if (open) {
    angle += 90;
    angleIncrements = -3;
  } else {
    angleIncrements = 3;
  }

  for (size_t i = 0; i < 30; i++) {
    angle += angleIncrements;
    ServoProcess(lidLeft, angle, PP_LID_LEFT);
  }
}

void MoveRightLid(bool open) {
  uint8_t angle;
  int8_t angleIncrements;

  angle = LID_OPEN_R;

  if (open) {
    angle -= 90;
    angleIncrements = 3;
  } else {
    angleIncrements = -3;
  }

  for (size_t i = 0; i < 30; i++) {
    angle += angleIncrements;
    ServoProcess(lidRight, angle, PP_LID_RIGHT);
  }
}

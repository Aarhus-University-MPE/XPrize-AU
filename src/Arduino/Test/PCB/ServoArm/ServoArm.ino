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

#define ANGLE_IDLE      90
#define ANGLE_FWD       180
#define ANGLE_REV       10

unsigned long lastmillisCycle = 0;

bool active = false;

Servo lidLeft, lidRight, armLeft, armRight;

void setup() {
  pinMode(A7, INPUT);
  pinMode(PO_SYSTEM_EN, OUTPUT);
  pinMode(PO_AIRFILTER_EN, OUTPUT);
  pinMode(PP_ARM_RIGHT, OUTPUT);
  pinMode(PP_ARM_LEFT, OUTPUT);
  pinMode(PP_LID_LEFT, OUTPUT);
  pinMode(PP_LID_RIGHT, OUTPUT);
  digitalWrite(PP_ARM_RIGHT, false);
  digitalWrite(PP_ARM_LEFT, false);
  digitalWrite(PP_LID_LEFT, false);
  digitalWrite(PP_LID_RIGHT, false);
}

void loop() {
  if (millis() - lastmillisCycle < PERIOD) return;

  if (analogRead(A7) > 800) {
    if (!active) {
      digitalWrite(PO_SYSTEM_EN, true);
      digitalWrite(LED_BUILTIN, true);
      active = true;
      delay(250);
    }

    // for (size_t i = 0; i < 80; i++) {
    //   SwingLeft(-1);
    // }

    // SwingLeft(0);
    // delay(500);

    // for (size_t i = 0; i < 80; i++) {
    //   SwingLeft(1);
    // }

    // SwingLeft(0);
    // delay(500);

    for (size_t i = 0; i < 80; i++) {
      SwingRight(-1);
    }

    SwingRight(0);
    delay(500);

    for (size_t i = 0; i < 80; i++) {
      SwingRight(1);
    }

    SwingRight(0);
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

void SwingLeft(int8_t direction) {
  if (direction == 0) {
    ServoProcess(armLeft, ANGLE_IDLE, PP_ARM_LEFT);
  } else if (direction > 0) {
    ServoProcess(armLeft, ANGLE_REV, PP_ARM_LEFT);
  } else {
    ServoProcess(armLeft, ANGLE_FWD, PP_ARM_LEFT);
  }
}

void SwingRight(int8_t direction) {
  if (direction == 0) {
    ServoProcess(armRight, ANGLE_IDLE, PP_ARM_RIGHT);
  } else if (direction < 0) {
    ServoProcess(armRight, ANGLE_REV, PP_ARM_RIGHT);
  } else {
    ServoProcess(armRight, ANGLE_FWD, PP_ARM_RIGHT);
  }
}
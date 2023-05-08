// Include the Servo library
#include <Ramp.h>
#include <Servo.h>

#define SPEED 80

int thrtlePin = A0;
int steerPin  = A3;
int fwdPin    = 2;
int bckPin    = 3;
int rightPin  = 4;
int leftPin   = 5;
int maxSteer  = 135;
int minSteer  = 45;
int timeStep  = 10;
int steerTrim = 3;

int speed = 90;

unsigned long lastMillisStutter = 0;

Servo Throttle, Steer;

rampInt steerAngle;
byte previousSteerAngle = 90;

void updateSteer(bool init = false) {
  int targetSteer;
  if (init) {
    targetSteer = 90 + steerTrim;
  } else if (!digitalRead(rightPin)) {
    targetSteer = maxSteer;
  } else if (!digitalRead(leftPin)) {
    targetSteer = minSteer;
  } else {
    targetSteer = 90 + steerTrim;
  }

  uint32_t duration = 1000. * (float)abs(steerAngle.getValue() - targetSteer) / SPEED;

  // start with going to the initial position
  if (init) {
    steerAngle.go(targetSteer);
    updateServo();
    delay(duration);
    return;
  }

  if (abs(targetSteer - previousSteerAngle) >= 2) {
    steerAngle.go(targetSteer, duration);  // set next ramp interpolation
    previousSteerAngle = targetSteer;      // save previous val
  }
}

void blink() {
  digitalWrite(LED_BUILTIN, true);
  delay(100);
  digitalWrite(LED_BUILTIN, false);
}

void updateServo() {
  int val = steerAngle.update();  // update ramp value
  Steer.write(steerAngle.getValue());
}

void updateThrottle() {
  Throttle.write(speed);
}

void setup() {
  Throttle.attach(thrtlePin);
  Steer.attach(steerPin);
  Throttle.write(90);

  updateSteer(true);
  digitalWrite(LED_BUILTIN, true);

  pinMode(fwdPin, INPUT_PULLUP);
  pinMode(bckPin, INPUT_PULLUP);
  pinMode(rightPin, INPUT_PULLUP);
  pinMode(leftPin, INPUT_PULLUP);
}

void loop() {
  if (!digitalRead(fwdPin)) {
    digitalWrite(LED_BUILTIN, true);
    speed = 110;
  } else if (!digitalRead(bckPin)) {
    digitalWrite(LED_BUILTIN, true);
    speed = 70;
  } else {
    digitalWrite(LED_BUILTIN, false);
    speed = 90;
  }

  updateSteer();
  updateServo();
  updateThrottle();
  delay(timeStep);
}
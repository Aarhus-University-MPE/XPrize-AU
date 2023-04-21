#include <Ramp.h>
#include <SBUS.h>
#include <Servo.h>

#define SPEED 80

SBUS sbus(Serial);

unsigned long millisLastSBusUpdate = 0;

const int thrtlePin = 5;
const int steerPin  = 3;
int throttle        = -1;
int steer           = -1;

const int maxSteer = 135;
const int minSteer = 45;

const float maxThrottleGain = 0.5f;
const int maxThrottle       = 90 * maxThrottleGain;

Servo servoThrottle;
Servo Steer;

rampInt steerAngle;
byte previousSteerAngle = 90;

const int minChannel = 364;
const int maxChannel = 1684;

// Scale the S.BUS channel values into the range [0, 256]
int getChannel(int channel) {
  int value = sbus.getChannel(channel);

  int mappedValue = map(value, minChannel, maxChannel, -100, 100);

  return mappedValue;
}

void updateSteer(bool init = false) {
  int steerInput = getChannel(1);
  int targetSteer;

  if (steerInput < -130) {
    targetSteer = 90;
  } else {
    targetSteer = map(steerInput, -100, 100, minSteer, maxSteer);
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

  Serial.end();
  Serial.begin(115200);
  Serial.print(steerInput);
  Serial.print("\t");
  Serial.println(targetSteer);
  Serial.end();
  sbus.begin(false);
}

void updateServo() {
  int val = steerAngle.update();  // update ramp value
  Steer.write(steerAngle.getValue());
}

void setup() {
  sbus.begin(false);
  servoThrottle.attach(thrtlePin);
  servoThrottle.write(90);
  Steer.attach(steerPin);
  updateSteer(true);
}

void loop() {
  if (millis() - millisLastSBusUpdate > 100) {
    throttle = getChannel(2);

    millisLastSBusUpdate = millis();
    if (throttle > -130) {
      servoThrottle.write(map(throttle, -100, 100, 90 - maxThrottle, 90 + maxThrottle));
    }
    updateSteer();
  } else {
    updateServo();
    sbus.process();
  }
}
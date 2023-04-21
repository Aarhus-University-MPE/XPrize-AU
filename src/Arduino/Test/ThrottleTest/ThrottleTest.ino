// Include the Servo library
#include <Servo.h>

int thrtlePin = 9;
int speed     = 90;

Servo Throttle;

void updateThrottle() {
  Serial.print("Setting Speed: ");
  Serial.println(speed);
  Throttle.write(speed);
}

void setup() {
  Throttle.attach(thrtlePin);
  Throttle.write(90);

  digitalWrite(LED_BUILTIN, true);

  Serial.begin(115200);
  Serial.println("Initialized");
}

void loop() {
  if (Serial.available()) {
    speed = Serial.parseInt();
    updateThrottle();
  }
}
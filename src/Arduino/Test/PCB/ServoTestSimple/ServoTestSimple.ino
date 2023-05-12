// Include the Servo library
#include <Servo.h>

#define PP_STEER     6
#define PO_SYSTEM_EN 4

#define PERIOD       200

Servo Steer;

unsigned long lastmillisCycle = 0;

bool turned = false;

void setup() {
  pinMode(A7, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PO_SYSTEM_EN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  if (millis() - lastmillisCycle < PERIOD) return;

  if (analogRead(A7) > 800) {
    digitalWrite(LED_BUILTIN, true);
    digitalWrite(PO_SYSTEM_EN, true);
    delay(500);
    if (!turned) {
      ServoProcess(Steer, 90, PP_STEER);
      turned = true;
    }
  } else {
    digitalWrite(LED_BUILTIN, false);
    digitalWrite(PO_SYSTEM_EN, false);
  }
}

const uint8_t servoPeriod = 200;

// Process a servo signal for a fixed period
void ServoProcess(Servo &servo, uint8_t angle, int servoPin) {
  servo.attach(servoPin);
  servo.write(angle);

  delay(servoPeriod);
  servo.detach();
}
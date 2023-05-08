// Include the Servo library
#include <Servo.h>

int lightPin = A1;

void setup() {
  Serial.begin(115200);
  Serial.println("Initialized");
  pinMode(lightPin, OUTPUT);
  digitalWrite(lightPin, false);
}

void loop() {
  if (Serial.available()) {
    switch (Serial.parseInt()) {
      case 1:
        digitalWrite(lightPin, true);
        Serial.println("Lights ON");
        break;
      case 2:
        digitalWrite(lightPin, false);
        Serial.println("Lights OFF");
        break;
      default:
        break;
    }
  }
}
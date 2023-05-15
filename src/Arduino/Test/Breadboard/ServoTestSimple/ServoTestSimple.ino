// Include the Servo library
#include <Servo.h>

#define PP_SERVO1 6
#define PP_SERVO2 7
#define PP_SERVO3 8

Servo servo1, servo2, servo3;

void setup() {
  servo1.attach(PP_SERVO1);
  servo1.write(0);
  servo1.attach(PP_SERVO2);
  servo1.write(90);
  servo1.attach(PP_SERVO3);
  servo1.write(180);
  digitalWrite(LED_BUILTIN, true);
}

void loop() {
}

void setup() {
  pinMode(A7, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop() {
  if (analogRead(A7) > 800) {
    digitalWrite(LED_BUILTIN, true);
    digitalWrite(4, true);
  } else {
    digitalWrite(LED_BUILTIN, false);
    digitalWrite(4, false);
  }
}
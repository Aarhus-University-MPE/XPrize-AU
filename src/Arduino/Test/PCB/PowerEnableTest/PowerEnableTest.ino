void setup() {
  pinMode(A7, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if (analogRead(A7) > 300) {
    digitalWrite(LED_BUILTIN, true);
  } else {
    digitalWrite(LED_BUILTIN, false);
  }
}
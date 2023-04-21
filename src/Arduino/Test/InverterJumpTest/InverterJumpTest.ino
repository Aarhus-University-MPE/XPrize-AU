const int invertPin = A0;

void setup() {
  pinMode(invertPin, INPUT);
}

void loop() {
  if (digitalRead(invertPin) != digitalRead(LED_BUILTIN)) digitalWrite(LED_BUILTIN, digitalRead(invertPin));
}
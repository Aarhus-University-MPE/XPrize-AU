#define PO_AIRFILTER_EN A0

void setup() {
  pinMode(A7, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PO_AIRFILTER_EN, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop() {
  if (analogRead(A7) > 800) {
    digitalWrite(LED_BUILTIN, true);
    digitalWrite(PO_AIRFILTER_EN, true);
    digitalWrite(4, true);
  } else {
    digitalWrite(LED_BUILTIN, false);
    digitalWrite(PO_AIRFILTER_EN, false);
    digitalWrite(4, false);
  }
}
const int batPin = A7;

const float R2 = 29.8;  // 39k Ohm
const float R1 = 520;   // 510 kOhmn

const float acdcFactor     = (1.1f / 1024.0f);
const float voltageDividor = R2 / (R1 + R2);

float voltageAcdc, voltageBat;

void setup() {
  analogReference(INTERNAL);

  Serial.begin(115200);
  Serial.println("Initialized");
}

void loop() {
  int read    = analogRead(batPin);
  voltageAcdc = read * acdcFactor;
  voltageBat  = voltageAcdc / voltageDividor;
  Serial.print(read);
  Serial.print("\t");
  Serial.print(voltageAcdc);
  Serial.print("\t");
  Serial.println(voltageBat);
  delay(500);
}
#define PA_SENSOR_BATT A6

const float R2 = 33;   // 39k Ohm
const float R1 = 510;  // 510 kOhmn

const float acdcFactor     = (1.1f / 1024.0f);
const float voltageDividor = R2 / (R1 + R2);

void setup() {
  analogReference(DEFAULT);

  Serial.begin(115200);
  Serial.println("Initialized");
}

void loop() {
  float batteryVoltage;
  int batteryVoltageInt;
  BatteryVoltage();
  // Serial.print("Output: ");
  // Serial.print(BatteryVoltage());
  // Serial.print(" V \t ");
  // Serial.println(BatteryVoltageInt());
  delay(500);
}

// Returns battery voltage x 1000 as an integer
int BatteryVoltageInt() {
  return (int16_t)(BatteryVoltage() * 1000.0f);
}

// Returns battery voltage as a float
float BatteryVoltage() {
  analogReference(INTERNAL);   // Set analog reference to internal for 1.1 voltage vMax
  analogRead(PA_SENSOR_BATT);  // Discard first reading

  // Read and convert analog battery voltage
  int read             = analogRead(PA_SENSOR_BATT);
  float voltageAcdc    = read * acdcFactor;
  float voltageBattery = voltageAcdc / voltageDividor;

  Serial.print(read);
  Serial.print("\t");
  Serial.print(voltageAcdc);
  Serial.print("\t");
  Serial.println(voltageBattery);

  analogReference(DEFAULT);  // Reset analog reference to default 5.0 voltage vMax

  return voltageBattery;
}
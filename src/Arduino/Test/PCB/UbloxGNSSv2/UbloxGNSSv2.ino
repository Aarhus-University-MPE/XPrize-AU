/*
  Program: Example1_NMEAsimple.ino
  Description:
  Prerequisites:
     1) NEO-M8N with SDA/SCL connected. Use pullups as necessary.
     2) LAST_SENTENCE_IN_INTERVAL has been set to GLL in NMEAGPS_cfg.h
*/
#include <NeoGPS_cfg.h>
#include <ublox/ubxGPS.h>

NMEAGPS gps;  // This parses the GPS characters
gps_fix fix;  // This holds on to the latest values

long lastTime = 0;  // Simple local timer. Limits amount if I2C traffic to u-blox module.

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;  // Wait for user to open terminal

  Serial.println("Example using Wire/I2C");

  pinMode(4, OUTPUT);
  digitalWrite(4, true);
  delay(1000);

  Wire.begin();
  Wire.setClock(400000);  // Increase I2C clock speed to 400kHz
}

void loop() {
  // Query module only every second. Doing it more often will just cause I2C traffic.
  // The module only responds when a new position is available
  if (millis() - lastTime > 1000) {
    while (gps.available(Wire)) {
      Serial.println("available");
      fix = gps.read();

      Serial.print("Location: ");
      if (fix.valid.location) {
        Serial.print(fix.latitude(), 6);
        Serial.print(',');
        Serial.print(fix.longitude(), 6);
      }

      Serial.print(", Altitude: ");
      if (fix.valid.altitude)
        Serial.print(fix.altitude());

      Serial.println();
    }
  }
}
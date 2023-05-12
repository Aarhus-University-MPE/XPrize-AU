#include <Wire.h>
#include <stdlib.h>

#define PRINT
#define commPin 9
int compassAdress = 0x21, slaveMicroControllerAddress = 2;
float currentLatitude, currentLongitude;

void setup() {
  pinMode(commPin, INPUT);
  Wire.begin();          // join i2c bus (address optional for master)
  Serial.begin(115200);  // start serial for output
}

void loop() {
  if (digitalRead(commPin) == HIGH)
    requestGPSData();
  else
    Serial.println("no gps data");

  delay(1000);
}

void requestGPSData() {
  char buffer[17];
  char *latEnd;
  Wire.requestFrom(slaveMicroControllerAddress, 17);  // request 8 bytes from slave device #2
  int i = 0;
  while (Wire.available())  // slave may send less than requested
  {
    buffer[i] = Wire.receive();  // receive a byte as character
    i++;
  }
  currentLatitude  = strtod(buffer, &latEnd);
  currentLongitude = strtod(latEnd, NULL);
#ifdef PRINT
  Serial.print("currentLatitude = ");
  Serial.print(currentLatitude, 5);
  Serial.print(" currentLongitude = ");
  Serial.println(currentLongitude, 5);
#endif
}
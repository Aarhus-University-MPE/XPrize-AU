#include <SBUS.h>

SBUS sbus(Serial);

unsigned long millisLastSBusUpdate = 0;

int throttle = -1;

const int minChannel = 364;
const int maxChannel = 1684;

// Scale the S.BUS channel values into the range [0, 256]
int getChannel(int channel) {
  int value = sbus.getChannel(channel);

  int mappedValue = map(value, 364, 1684, -100, 100);

  return mappedValue;
}

void setup() {
  sbus.begin(false);
}

void loop() {
  if (millis() - millisLastSBusUpdate > 1000) {
    throttle = getChannel(2);

    millisLastSBusUpdate = millis();
    Serial.end();
    Serial.begin(115200);
    Serial.println(throttle);
    Serial.end();
    sbus.begin(false);
  } else {
    sbus.process();
  }
}
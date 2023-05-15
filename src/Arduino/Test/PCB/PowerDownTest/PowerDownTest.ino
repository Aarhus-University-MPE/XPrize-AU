#include <LowPower.h>

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void blink() {
  digitalWrite(LED_BUILTIN, true);
  delay(2000);
  digitalWrite(LED_BUILTIN, false);
}

void loop() {
  blink();
  SleepDuration(9);
}

// Sleep for x times 9 seconds, (rounded down)
void SleepDuration(uint16_t seconds) {
  uint16_t sleepCycles = seconds / 9;  // 8 sec sleep + 1 sec wakeup time-> Sleep

  for (size_t i = 0; i < sleepCycles; i++) {
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }
}

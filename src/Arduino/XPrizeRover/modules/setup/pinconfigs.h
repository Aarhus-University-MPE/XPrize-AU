#pragma once

#include "./modules.h"

// Initialization of inputs
void InitInterrupts() {
  // Switch Mode interrupt
  // attachInterrupt(PT_ENCODER_Z, EncoderZInterrupt, RISING);  // Triggers once every revolution
}

// Sets pinmode of all pins and writes initial values for outputs
void InitAllPins() {
  // Motor
  // digitalWrite(PO_MOTOR_ARM_LEFT, LOW);
  // digitalWrite(PO_MOTOR_ARM_RIGHT, LOW);
  // digitalWrite(PO_MOTOR_LATCH_LEFT, LOW);
  // digitalWrite(PO_MOTOR_LATCH_RIGHT, LOW);

  // pinMode(PO_MOTOR_ARM_LEFT, OUTPUT);
  // pinMode(PO_MOTOR_ARM_RIGHT, OUTPUT);
  // pinMode(PO_MOTOR_LATCH_LEFT, OUTPUT);
  // pinMode(PO_MOTOR_LATCH_RIGHT, OUTPUT);

  // Communication
  // pinMode(PO_SPISS_SDCARD, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  // Interrupts
  InitInterrupts();
}

// Check for Up Button noise, returns true if valid button press
// bool UpButtonDebounce() {
//   if (millis() - lastMillisUp < BTN_DEBOUNCE_TIME) {
//     return false;
//   }

//   // Small time delay to filter voltage spikes
//   delay(50);

//   // Check if button is still pressed
//   if (digitalRead(PI_BUTTON_MOTOR_UP)) {
//     return false;
//   }

//   // Set timestamp for button debouncing
//   lastMillisUp = millis();
//   return true;
// }
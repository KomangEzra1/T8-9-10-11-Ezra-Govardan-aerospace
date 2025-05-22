#include "UrusanBuzzer.h"

UrusanBuzzer::UrusanBuzzer(uint8_t pinBuz, uint16_t freq) 
  : _pinBuzzer(pinBuz), _freq(freq) {
  pinMode(_pinBuzzer, OUTPUT);
  noTone(_pinBuzzer); // Ensure the buzzer is off initially
}

void UrusanBuzzer::beep(uint32_t delayMs, uint8_t beepCount) {
  for (uint8_t i = 0; i < beepCount; i++) {
    tone(_pinBuzzer, _freq); // Start the buzzer
    delay(delayMs);          // Wait for the specified ON duration
    noTone(_pinBuzzer);      // Stop the buzzer
    delay(delayMs);          // Wait for the specified OFF duration
  }
}
#ifndef UrusanBuzzer_h
#define UrusanBuzzer_h

#include "Arduino.h"

class UrusanBuzzer {
  public:
    UrusanBuzzer(uint8_t pinBuz, uint16_t freq = 1600); // Default frequency is 1600 Hz
    void beep(uint32_t delayMs, uint8_t beepCount); // Blocking beep function

  private:
    uint8_t _pinBuzzer;
    uint16_t _freq;
};

#endif
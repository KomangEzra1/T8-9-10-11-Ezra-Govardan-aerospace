#ifndef UrusanLED_h
#define UrusanLED_h

#include "Arduino.h"

class UrusanLED {
  public:
    UrusanLED(uint8_t pinR, uint8_t pinG, uint8_t pinB);
    void setWarna(uint8_t r, uint8_t g, uint8_t b);

  private:
    uint8_t _pinR;
    uint8_t _pinG;
    uint8_t _pinB;
    int _chanR;
    int _chanG;
    int _chanB;
    void _aturPinPWM(int channel, uint8_t value);
};

#endif
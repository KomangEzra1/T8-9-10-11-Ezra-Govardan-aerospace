#include "UrusanLED.h"

UrusanLED::UrusanLED(uint8_t pinR, uint8_t pinG, uint8_t pinB) : _pinR(pinR), _pinG(pinG), _pinB(pinB),
_chanR(0), _chanG(1), _chanB(2) {
  // Setup channels for PWM
  ledcSetup(_chanR, 5000, 8); // Channel R, 5 kHz, 8-bit resolution
  ledcSetup(_chanG, 5000, 8); // Channel G, 5 kHz, 8-bit resolution
  ledcSetup(_chanB, 5000, 8); // Channel B, 5 kHz, 8-bit resolution

  // Attach pins to channels
  ledcAttachPin(_pinR, _chanR);
  ledcAttachPin(_pinG, _chanG);
  ledcAttachPin(_pinB, _chanB);
}

void UrusanLED::setWarna(uint8_t r, uint8_t g, uint8_t b) {
  _aturPinPWM(_chanR, map(r, 0, 100, 0, 255));
  _aturPinPWM(_chanG, map(g, 0, 100, 0, 255));
  _aturPinPWM(_chanB, map(b, 0, 100, 0, 255));
}

void UrusanLED::_aturPinPWM(int channel, uint8_t value) {
  ledcWrite(channel, value);
}
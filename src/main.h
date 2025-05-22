#ifndef MAIN_H
#define MAIN_H
#include <Arduino.h>
#include <Wire.h>
#include <params.h>
#include <secret.h>
#include <UrusanWiFi.h>
#include <UrusanLED.h>
#include <UrusanOLED.h>
#include <UrusanBuzzer.h>


// Tulis parameter lokal mu di sini
const uint8_t pinLEDMerah = 27;
const uint8_t pinLEDHijau = 26;
const uint8_t pinLEDBiru = 25;
const uint8_t pinBuzzer = 13;

// Tulis instansiasi objek global mu di sini
UrusanWiFi urusanWiFi(wssid);
UrusanLED urusanLED(pinLEDMerah, pinLEDHijau, pinLEDBiru);
UrusanOLED oled;
UrusanBuzzer buzzer(pinBuzzer);

// Tulis deklarasi fungsi mu di sini:
void cetakIdentitasDeveloper();
void i2cScanner();

#endif

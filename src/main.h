#ifndef MAIN_H
#define MAIN_H
#include <Arduino.h>
#include <params.h>
#include <secret.h>
#include <UrusanWiFi.h>
#include <UrusanIoT.h>
#include <ArduinoJson.h>
#include <UrusanLED.h>
#include <UrusanOLED.h>
#include <Wire.h>


// Tulis parameter lokal mu di sini
uint8_t currentSlide = 0;
uint8_t maxSlide = 5; // Untuk mengatur tampilan slider
bool HIDUP = false; // State hidup relay
bool relayStates[4] = {false, false, false, false};
uint8_t pinrelays[4] = {27, 26, 25, 33}; // Pin untuk relay 1-4
String clientId = String(CURRENT_FIRMWARE_TITLE) + String(NIM) + String("-") + String(random(1, 9999)); // Client ID untuk MQTT
unsigned long lastSent = 0;
bool flagUpdate = false;
float lastLux = 0;
float lastTemp = 0;
float lastHumid = 0;
float lastTankLevel = 0;
float lastTankDistance = 0;
uint8_t lastBlowerSpeed = 0;
bool lastBlowerDirection = 0;
bool lastBlowerState = 0;


int luxBottomThreshold = 1000;
int luxUpperThreshold = 4000;
float tempBottomThreshold = 0;
float tempUpperThreshold = 100;
float humidBottomThreshold = 0;
float humidUpperThreshold = 100;
float tankLevelBottomThreshold = 0;
float tankLevelUpperThreshold = 100;


// Tulis instansiasi objek global mu di sini
UrusanWiFi urusanWiFi(wssid, wpass);
UrusanIoT urusanIoT(tbAddr, tbPort, clientId.c_str(), "latihan", "bukanbudakai");
UrusanOLED urusanOLED;


// Tulis deklarasi fungsi mu di sini:
void cetakIdentitasDeveloper();
void penangkapPesan(String topic, String message);
void subscribe();
void screenSlider();


#endif

#include <main.h>


void setup() {
  // tulis setup kode mu di sini, untuk dijalankan sekali saja:  
  Serial.begin(115200);
  urusanOLED.mulai();
  urusanOLED.bersihkan();


  Wire.begin();


  for(int i = 0; i < 4; i++) {
    pinMode(pinrelays[i], OUTPUT);
    digitalWrite(pinrelays[i], !HIDUP);
  }


  urusanWiFi.konek();
  while(urusanWiFi.apakahKonek() == 0){
    Serial.print(".");
  }


  urusanIoT.konek();
  urusanIoT.penangkapPesan(penangkapPesan);


  if(urusanIoT.apakahKonek() == 1){
    subscribe();
  }


  cetakIdentitasDeveloper();
  delay(3000);
}


unsigned long lastUpdateMillis = 0;
unsigned long lastSliderMillis = 0;
void loop() {
  // tulis kode utama mu di sini, untuk dijalankan berulang-ulang :
  urusanIoT.proses();


  if(urusanIoT.apakahKonek() == 0){
    Serial.println("UrusanIoT: Koneksi terputus, mencoba untuk menyambung kembali...");
    urusanIoT.konek();
    if(urusanIoT.apakahKonek() == 1){
      subscribe();
    }
  }


  if (millis() - lastUpdateMillis >= 1000) {
    lastUpdateMillis = millis();


    String payload;
    JsonDocument doc;
    doc["relay1"] = relayStates[0];
    doc["relay2"] = relayStates[1];
    doc["relay3"] = relayStates[2];
    doc["relay4"] = relayStates[3];
    serializeJson(doc, payload);


    urusanIoT.publish("Aerospace/govardan/status", payload);
  }


  if (millis() - lastSliderMillis >= 3000) {
    lastSliderMillis = millis();
    screenSlider();
  }


  delay(10);
}


void subscribe() {
  urusanIoT.subscribe("Aerospace/gadadar/status");
  urusanIoT.subscribe("Aerospace/damodar/status");
  urusanIoT.subscribe("Aerospace/murari/status");
  urusanIoT.subscribe("Aerospace/sudarsan/status");
  urusanIoT.subscribe("Aerospace/govardan/command");
}


void penangkapPesan(String topic, String message){
  Serial.printf("penangkapPesan: topic: %s | message: %s\r\n", topic.c_str(), message.c_str());
  JsonDocument dataMasuk;
  DeserializationError galatParseJson = deserializeJson(dataMasuk, message);
  if(galatParseJson == DeserializationError::Ok){
    if(topic == "namakelompok/govardan/command") {
      if(dataMasuk["relay1"].is<bool>()) {
        relayStates[0] = dataMasuk["relay1"];
        digitalWrite(pinrelays[0], dataMasuk["relay1"].as<bool>() == true ? HIDUP : !HIDUP);
      }
      if(dataMasuk["relay2"].is<bool>()) {
        relayStates[1] = dataMasuk["relay2"];
        digitalWrite(pinrelays[1], dataMasuk["relay2"].as<bool>() == true ? HIDUP : !HIDUP);
      }
      if(dataMasuk["relay3"].is<bool>()) {
        relayStates[2] = dataMasuk["relay3"];
        digitalWrite(pinrelays[2], dataMasuk["relay3"].as<bool>() == true ? HIDUP : !HIDUP);
      }
      if(dataMasuk["relay4"].is<bool>()) {
        relayStates[3] = dataMasuk["relay4"];
        digitalWrite(pinrelays[3], dataMasuk["relay4"].as<bool>() == true ? HIDUP : !HIDUP);
      }
    }
    else if(topic == "Aerospace/murari/status"){
      if(dataMasuk["temp"].is<float>()) {
        lastTemp = dataMasuk["temp"];
      }
      if(dataMasuk["humid"].is<float>()) {
        lastHumid = dataMasuk["humid"];
      }
    }
    else if(topic == "Aerospace/damodar/status"){
      Serial.println("penangkapPesan: Menerima status dari Damodar");
      if(dataMasuk["tankLevel"].is<float>()) {
        lastTankLevel = dataMasuk["tankLevel"];
        Serial.printf("Tank Level: %.2f\r\n", lastTankLevel);
      }
      if(dataMasuk["tankDistance"].is<float>()) {
        lastTankDistance = dataMasuk["tankDistance"];
        Serial.printf("Tank Distance: %.2f\r\n", lastTankDistance);
      }
    }
    else if(topic == "Aerospace/sudarsan/status"){
      Serial.println("penangkapPesan: Menerima status dari Sudarsan");
      if(dataMasuk["blowerSpeed"].is<uint8_t>()) {
        lastBlowerSpeed = dataMasuk["blowerSpeed"];
        Serial.printf("Blower Speed: %d\r\n", lastBlowerSpeed);
      }
      if(dataMasuk["blowerDirection"].is<bool>()) {
        lastBlowerDirection = dataMasuk["blowerDirection"];
        Serial.printf("Blower Direction: %s\r\n", lastBlowerDirection ? "Forward" : "Reverse");
      }
      if(dataMasuk["blowerState"].is<bool>()) {
        lastBlowerState = dataMasuk["blowerState"];
        Serial.printf("Blower State: %s\r\n", lastBlowerState ? "On" : "Off");
      }
    }
  }
  else
  {
    Serial.printf("penangkapPesan: Gagal parse JSON: %s\r\n", galatParseJson.c_str());
  }
}


void screenSlider() {
  if(currentSlide == 0){
    urusanOLED.bersihkan();
    urusanOLED.tambahTeks(0, 0, "Relay 1: %s", relayStates[0] ? "Hidup" : "Mati");
    urusanOLED.tambahTeks(0, 8, "Relay 2: %s", relayStates[1] ? "Hidup" : "Mati");
    urusanOLED.tambahTeks(0, 16, "Relay 3: %s", relayStates[2] ? "Hidup" : "Mati");
    urusanOLED.tambahTeks(0, 24, "Relay 4: %s", relayStates[3] ? "Hidup" : "Mati");
    urusanOLED.tampilkan();
  }else if(currentSlide == 1){
    urusanOLED.bersihkan();
    urusanOLED.tambahTeks(0, 0, "Temperatur: %.2f C", lastTemp);
    urusanOLED.tambahTeks(0, 8, "Kelembaban: %.2f %%", lastHumid);
    urusanOLED.tampilkan();
  }
  else if(currentSlide == 2){
    urusanOLED.bersihkan();
    urusanOLED.tambahTeks(0, 0, "Tanki Air: %.2f %%", lastTankLevel);
    urusanOLED.tambahTeks(0, 8, "Jarak Tanki: %.2f cm", lastTankDistance);
    urusanOLED.tampilkan();
  }
  else if(currentSlide == 3){
    urusanOLED.bersihkan();
    urusanOLED.tambahTeks(0, 0, "Lux: %.2f", lastLux);
    urusanOLED.tampilkan();
  }
  else if(currentSlide == 4){
    urusanOLED.bersihkan();
    urusanOLED.tambahTeks(0, 0, "Kecepatan Blower: %d", lastBlowerSpeed);
    urusanOLED.tambahTeks(0, 8, "Arah Blower: %s", lastBlowerDirection ? "Maju" : "Mundur");
    urusanOLED.tambahTeks(0, 16, "Status Blower: %s", lastBlowerState ? "Hidup" : "Mati");
    urusanOLED.tampilkan();
  }


  currentSlide++;
  if(currentSlide > maxSlide) {
    currentSlide = 0;
  }
}


// tulis definisi fungsi mu di sini:
void cetakIdentitasDeveloper() {
  urusanOLED.bersihkan();
  urusanOLED.tambahTeks(0, 0, "%d", NIM);
  urusanOLED.tambahTeks(0, 8, "%s", NAMA_LENGKAP);
  urusanOLED.tambahTeks(0, 16, "%s", NAMA_KELOMPOK);
  urusanOLED.tambahTeks(0, 24, "%s %s", CURRENT_FIRMWARE_TITLE, CURRENT_FIRMWARE_VERSION);
  urusanOLED.tampilkan();


  Serial.printf("NIM: %d\r\n", NIM);
  Serial.printf("Nama: %s\r\n", NAMA_LENGKAP);
  Serial.printf("Grup: %s\r\n", NAMA_KELOMPOK);
  Serial.printf("Firmware: %s %s\r\n", CURRENT_FIRMWARE_TITLE, CURRENT_FIRMWARE_VERSION);
}

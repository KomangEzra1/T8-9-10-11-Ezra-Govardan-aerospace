#include <main.h>


void setup() {
  // tulis setup kode mu di sini, untuk dijalankan sekali saja:
  urusanLED.setWarna(100, 0, 0);
 
  Wire.begin();
  Serial.begin(SERIAL_BAUD_RATE);
  i2cScanner();
 
  oled.mulai();
  oled.bersihkan();
 
  cetakIdentitasDeveloper();


  urusanWiFi.konek();
  while(urusanWiFi.apakahKonek() == 0){
    Serial.print(".");
    delay(1000);
  }
  urusanLED.setWarna(0, 100, 0);
  buzzer.beep(50, 3);
  buzzer.beep(100, 2);


  // Start MQTT
  urusanIoT.konek();
  urusanIoT.penangkapPesan(penangkapPesan);


  if(urusanIoT.apakahKonek() == 1){
    subscribe();
  }
}


unsigned long lastSent = 0;
void loop() {
  // tulis kode utama mu di sini, untuk dijalankan berulang-ulang :
  urusanIoT.proses();


  if (millis() - lastSent > 1000) {
    String pesan = String(NAMA_LENGKAP) + " - " + String(NIM) + " - " + String("HADIR");
    urusanIoT.publish("undiknas/psti/display/update", pesan);
    lastSent = millis();
  }
}


void penangkapPesan(String topic, String message){
  Serial.printf("penangkapPesan: topic: %s | message: %s\r\n", topic.c_str(), message.c_str());
  oled.bersihkan();
  oled.tambahTeks(0, 0, "%s", message.c_str());  
  oled.tampilkan();
}


// tulis definisi fungsi mu di sini:
void cetakIdentitasDeveloper() {
  oled.tambahTeks(0, 0, "%d", NIM);  
  oled.tampilkan();
  oled.tambahTeks(0, 10, "%s", NAMA_LENGKAP);
  oled.tampilkan();
  oled.tambahTeks(0, 20, "%s", NAMA_KELOMPOK);
  oled.tampilkan();
  oled.tambahTeks(0, 30, "%s %s", CURRENT_FIRMWARE_TITLE, CURRENT_FIRMWARE_VERSION);
  oled.tampilkan();
}


void subscribe() {
  urusanIoT.subscribe("undiknas/psti/display");
  urusanIoT.subscribe("undiknas/psti/display/update");
}


void i2cScanner() {
  byte error, address;
  int nDevices;


  Serial.println("Scanning...");


  nDevices = 0;
  for(address = 1; address < 127; address++ ) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.print(address, HEX);
      Serial.println(" !");
      nDevices++;
    } else if (error == 4) {
      Serial.print("Unknow error at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  } else {
    Serial.println("done\n");
  }
}

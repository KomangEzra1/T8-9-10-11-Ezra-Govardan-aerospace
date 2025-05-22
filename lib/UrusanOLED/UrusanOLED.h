#ifndef UrusanOLED_h
#define UrusanOLED_h

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class UrusanOLED {
  public:
    UrusanOLED();
    void mulai();
    void bersihkan();
    void tambahTeks(int x, int y, const char* format, ...);
    void tampilkan();

  private:
    Adafruit_SSD1306 display;
};

#endif
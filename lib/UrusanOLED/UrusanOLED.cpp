#include "UrusanOLED.h"

UrusanOLED::UrusanOLED() : display(128, 64, &Wire) {}

void UrusanOLED::mulai() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Ganti 0x3C dengan alamat OLED Anda jika berbeda
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Jangan lanjutkan, loop selamanya
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
}

void UrusanOLED::bersihkan() {
  display.clearDisplay();
}

void UrusanOLED::tambahTeks(int x, int y, const char* format, ...) {
    char buffer[128]; // Create a buffer to hold the formatted string
    va_list args;     // Declare a variable argument list
    va_start(args, format); // Initialize the argument list
    vsnprintf(buffer, sizeof(buffer), format, args); // Format the string
    va_end(args);     // Clean up the argument list
  
    display.setCursor(x, y); // Set the cursor position
    display.print(buffer);   // Print the formatted string to the display
}

void UrusanOLED::tampilkan() {
  display.display();
}

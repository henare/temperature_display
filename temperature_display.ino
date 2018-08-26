#include "SSD1306Spi.h"

// Initialize the OLED display using SPI
// D5 -> CLK (Display D0)
// D7 -> MOSI (DOUT) (Display D1)
// D0 -> RES
// D2 -> DC
// D8 -> CS
SSD1306Spi        display(D0, D2, D8);

void setup() {
  Serial.begin(9600);
  Serial.println("starting...");
  Serial.println();

  // Initialising the UI will init the display too.
  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

  display.clear();
  drawTemperature();
  display.display();
}

void drawTemperature() {
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_16);
    display.drawString(64, 0, "Inside");
    display.setFont(ArialMT_Plain_24);
    display.drawString(64, 16, "24.6°");
}

void loop() {
//  delay(10);
}

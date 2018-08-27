#include "SSD1306Spi.h"
// Initialize the OLED display using SPI
// D5 -> CLK (Display D0)
// D7 -> MOSI (DOUT) (Display D1)
// D0 -> RES
// D2 -> DC
// D8 -> CS
SSD1306Spi        display(D0, D2, D8);

#include "DHT.h"
#define DHTPIN D6
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("Starting setup...");
  Serial.println();

  dht.begin();

  // Initialising the UI will init the display too.
  display.init();
  // Displays the yellow bar on the top
  display.flipScreenVertically();
}

void loop() {
  // Run every 10 seconds
  delay(10000);

  // Output display
  display.clear();

  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_16);
  display.drawString(64, 0, "Inside");
  display.setFont(ArialMT_Plain_24);
  display.drawString(64, 16, insideTemperature());

  display.display();
}

String insideTemperature() {
  float temperature = dht.readTemperature();
  // Checks for failure and retries
  if (isnan(temperature)) {
    Serial.println("Failed to read temperature.");
    return "-";
  } else {
    return Float2String(temperature, 1) + "°";
  }
}

/*****************************************************************
/* convert float to string                                       *
/*****************************************************************/
String Float2String(const double value, unsigned int digits) {
  char temp[15];
  String s;

  dtostrf(value, 13, digits, temp);
  s = String(temp);
  s.trim();
  return s;
}

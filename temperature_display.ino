#include "font.h"

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

#include <ESP8266WiFi.h>
#include "wifi_settings.h"

void setup() {
  Serial.begin(9600);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  dht.begin();

  // Initialising the UI will init the display too.
  display.init();
  // Displays the yellow bar on the top
  display.flipScreenVertically();
}

void loop() {
  float insideTemperature = dht.readTemperature();
  float outsideTemperature = -2.2;

  display.clear();
  if (insideTemperature > outsideTemperature) {
    display.invertDisplay();
  } else {
    display.normalDisplay();
  }
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_16);
  display.drawString(64, 0, "Inside");
  display.setFont(Roboto_Bold_40);
  display.drawString(64, 16, displayTemperature(insideTemperature));
  display.display();

  delay(5000);

  display.clear();
  if (outsideTemperature > insideTemperature) {
    display.invertDisplay();
  } else {
    display.normalDisplay();
  }
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_16);
  display.drawString(64, 0, "Outside");
  display.setFont(Roboto_Bold_40);
  display.drawString(64, 16, displayTemperature(outsideTemperature));
  display.display();

  // Refresh every 10 seconds
  delay(5000);
}

String displayTemperature(float temperature) {
  if (isnan(temperature)) {
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

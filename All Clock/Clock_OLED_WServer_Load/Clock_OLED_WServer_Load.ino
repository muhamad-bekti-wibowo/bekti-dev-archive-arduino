#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include "index.h"
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char *ssid     = "Internet Gratis";
const char *password = "";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
const char* PARAM_MESSAGE = "message";
AsyncWebServer server(80);
void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}
String _on = "10", _off = "20" , _time ;

void setup() {
  Serial.begin(115200);
  Wire.begin(0, 2);
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  timeClient.begin();
  timeClient.setTimeOffset(25200);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/html", jadwal);
  });
  server.on("/jadwal", HTTP_GET, [] (AsyncWebServerRequest * request) {
    String message;
    if (request->hasParam("on")) {
      _on = request->getParam("on")->value();
    }
    if (request->hasParam("off")) {
      _off = request->getParam("off")->value();
    }
    request->send(200, "text/plain", "OK");
  });
  server.on("/time", HTTP_GET, [] (AsyncWebServerRequest * request) {

    request->send(200, "text/plain", _time.c_str());
  });
  server.onNotFound(notFound);

  server.begin();
  display.display();
  delay(2000);
  display.clearDisplay();
  pinMode(14, OUTPUT);
  digitalWrite(14, 0);
}

void loop() {
  timeClient.update();
  _time = timeClient.getFormattedTime();
  if (timeClient.getSeconds() < _off.toInt() && timeClient.getSeconds() > _on.toInt() )
    digitalWrite(14, 1);
  else
    digitalWrite(14, 0);

  Serial.println(_on);
  Serial.println(_off);
  Serial.println(_time);
  display.clearDisplay();
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0, 0);
  display.print(_time);
  display.setCursor(0, 20);
  display.print(_on);
  display.setCursor(0, 40);
  display.print(_off);
  display.display();
  delay(1000);
}

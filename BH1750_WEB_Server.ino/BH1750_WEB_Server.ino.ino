#include <Wire.h>
#include <BH1750.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "index.h"
AsyncWebServer server(80);

const char* ssid = "MIFON";
const char* password = "";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}
float lux;
BH1750 lightMeter;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  lightMeter.begin();
  Serial.println(F("BH1750 Test begin"));
  WiFi.mode(WIFI_STA);
  WiFi.hostname("BH1750");
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.printf("WiFi Failed!\n");
    return;
  }
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/html", _index);
  });
  server.on("/lux", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/plain", ((String)lux).c_str());
  });
  server.onNotFound(notFound);
  server.begin();
}

void loop() {
  lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lux");
  delay(1000);
}

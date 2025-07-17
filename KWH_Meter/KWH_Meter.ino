#include <Server.h>
#include <ESP8266WiFi.h>
#include <PZEM004Tv30.h>

#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
AsyncWebServer server(80);
#include "index.h"

/* Use software serial for the PZEM
   Pin 11 Rx (Connects to the Tx pin on the PZEM)
   Pin 12 Tx (Connects to the Rx pin on the PZEM)
*/
PZEM004Tv30 pzem(12, 13 );
String data;
uint64_t PM;
bool state =  1;
void arrdata() {
  data = String(pzem.voltage())  + "~" +
         String(pzem.current()) + "~" +
         String(pzem.power()) + "~" +
         String(pzem.energy()) + "~" +
         String(pzem.frequency())  + "~" +
         String(pzem.pf()) + "~";
  Serial.println(data);
}
void Server_() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    request->send_P(200, "text/html", KWH);
  });
  server.on("/reset", HTTP_GET, [](AsyncWebServerRequest * request)
  { pzem.resetEnergy();
    request->send_P(200, "text/html", "OK");
  });
  server.on("/state", HTTP_GET, [](AsyncWebServerRequest * request)
  { state = !state;
    request->send_P(200, "text/html", "OK");
  });
  server.on("/data", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    request->send(200, "text/plain", String(data).c_str());
  });
  server.begin();
}
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  Serial.print("Created Wifi AP");
  WiFi.hostname("KWH");
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());
  Serial.print("Conneting to Free Intentet");
  WiFi.begin("Free Internet");
  pinMode(2, OUTPUT);
  pinMode(14, OUTPUT);
  bool leds;
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    leds = !leds;
    digitalWrite(2, leds);
  }
  Server_();
}

void loop() {
  if (millis() - PM >= 1000)
  { PM = millis();
    digitalWrite(2, state);
    digitalWrite(14, state);
    arrdata();

  }
}

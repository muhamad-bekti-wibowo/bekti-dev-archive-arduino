#include <Arduino.h>
#include "PIN.h"
#include <IRremote.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);
int RECV_PIN = 5;

IRrecv irrecv(RECV_PIN);
decode_results results;

const char* ssid = "Free Internet";
const char* password = "";

void setup() {
  Serial.begin(115200);
  irrecv.enableIRIn();
  Serial.println(IR_SEND_PIN);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) { return; }
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    IrSender.sendNEC(0X707030CF);
    request->send(200, "text/plain", "ON OFF TV");
  });
  server.begin();
}
void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume();
  }
}

#include <Arduino.h>

#include <ESP8266WiFi.h>

#include <NTPClient.h>
#include <WiFiUdp.h>

#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "index.h"

#include <IRremote.h>

const char *ssid     = "Free Internet";
const char *password = "";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

AsyncWebServer server(80);

int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}
String data_IR, data, _time ;
int _on, _off ;
uint64_t PM;
bool  kipas , lampu1 , lampu2, ir, automatic, lampu3;
void data_arr() {
  data = (String)ir + "~" +   (String) lampu2 + "~" +    (String)kipas + "~" +    (String)lampu1 + "~" +   (String)automatic + "~" + (String)lampu3 ;
  Serial.println(data);
}
void setup() {
  //Serial.begin(115200);
  pinMode(0, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);

  pinMode(14, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(16, OUTPUT);

  digitalWrite(14, 1);
  digitalWrite(12, 1);
  digitalWrite(13, 1);
  digitalWrite(16, 1);
  WiFi.hostname("Depan");
  irrecv.enableIRIn();

  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  timeClient.begin();
  timeClient.setTimeOffset(25200);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/html", jadwal);
  });
  server.on("/jadwal", HTTP_GET, [] (AsyncWebServerRequest * request) {
    String message;
    if (request->hasParam("on")) {
      _on = request->getParam("on")->value().toInt();
    }
    if (request->hasParam("off")) {
      _off = request->getParam("off")->value().toInt();
    }
    if (request->hasParam("ir")) {
      ir = request->getParam("ir")->value() == "on" ? 0 : 1;
    }
    else {
      ir = 1;
    }
    if (request->hasParam("lrt")) {
      lampu2 = request->getParam("lrt")->value() == "on" ? 0 : 1;
    }
    else {
      lampu2 = 1;
    }
    if (request->hasParam("lampu3")) {
      lampu3  = request->getParam("lampu3")->value() == "on" ? 0 : 1;
    }

    else {
      lampu3  = 1;
    }
    if (request->hasParam("auto")) {
      automatic = request->getParam("auto")->value() == "on" ? 1 : 0;
    }

    else {
      automatic = 0;
    }
    if (request->hasParam("krt")) {
      kipas = request->getParam("krt")->value() == "on" ? 0 : 1;
    }
    else {
      kipas = 1;
    }
    if (request->hasParam("rm")) {
      lampu1 = request->getParam("rm")->value() == "on" ? 0 : 1;
    }
    else {
      lampu1 = 1;
    }
    request->send(200, "text/plain", "OK");
  });
  server.on("/time", HTTP_GET, [] (AsyncWebServerRequest * request) {

    request->send(200, "text/plain", _time.c_str());
  });
  server.on("/data", HTTP_GET, [] (AsyncWebServerRequest * request) {
    data_arr();
    request->send(200, "text/plain", data.c_str());
  });
  server.onNotFound(notFound);
  _on = 5;
  _off = 18;
  server.begin();
}

void loop() {
  if (millis() - PM >= 1000) {
    timeClient.update();
    _time = timeClient.getFormattedTime();
    if ( automatic) {
      if ( timeClient.getHours() > _on && timeClient.getHours()< _off )
        lampu3 = 1;
      else
        lampu3 = 0;
      //Serial.println(timeClient.getSeconds());
    }
    PM = millis();
  }
  if (!ir) {
    if (irrecv.decode(&results))
    {
      if (results.value  == 1886421119 ) {
        kipas = !kipas;
        delay(1000);
      }
      if ( results.value == 1886404799 ) {
        lampu1 = !lampu1;
        delay(1000);
      }
      if ( results.value == 1886437439) {
        lampu2 = !lampu2;
        delay(1000);
      }
      irrecv.resume();
    }
  }
  if (!digitalRead(0) ) {
    kipas = !kipas;
    delay(1000);
  }
  if (!digitalRead(4) ) {
    lampu1 = !lampu1;
    delay(1000);
  }
  if (!digitalRead(5) ) {
    lampu2 = !lampu2;
    delay(1000);
  }
//    if (!digitalRead(1) ) {
//      lampu3 = !lampu3; automatic = 0;    delay(1000);
//    }
  irrecv.resume();
  digitalWrite(12, lampu3);
  digitalWrite(16, lampu2);
  digitalWrite(14, kipas);
  digitalWrite(13, lampu1);
}

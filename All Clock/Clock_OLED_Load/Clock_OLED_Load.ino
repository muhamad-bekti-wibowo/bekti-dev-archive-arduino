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

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

#define OLED_RESET     4 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char *ssid     = "Internet Gratis";
const char *password = "";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

String _on = "5", _off = "18" , _time ;

void setup() {
  Serial.begin(115200);
  //Wire.begin(0, 2);
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  timeClient.begin();
  timeClient.setTimeOffset(25200);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.display();
  delay(2000);
  display.clearDisplay();
  pinMode(14, OUTPUT);
  digitalWrite(14, 0);
}

void loop() {
  timeClient.update();
  _time = timeClient.getFormattedTime();
  if (timeClient.getHours() < _off.toInt() && timeClient.getHours() > _on.toInt() )
    digitalWrite(14, 1);
  else
    digitalWrite(14, 0);
    
  Serial.println(_on);
  Serial.println(_off);
  Serial.println(_time);
  
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print(_time);
  display.setCursor(0, 20);
  display.print(_on);
  display.setCursor(0, 40);
  display.print(_off);
  display.display();
  delay(1000);
}

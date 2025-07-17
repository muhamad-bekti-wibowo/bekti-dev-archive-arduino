#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
const char *ssid     = "Internet Gratis";
const char *password = "";
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
int _on = 5, _off = 19 ;
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  timeClient.begin();
  timeClient.setTimeOffset(25200);
  pinMode(14, OUTPUT);
  digitalWrite(14, 0);
}

void loop() {
  timeClient.update();
  Serial.println(timeClient.getFormattedTime());
  delay(1000);
  if (timeClient.getHours() < _off && timeClient.getHours() > _on )
    digitalWrite(14, 0);
  else
    digitalWrite(14, 1);
}

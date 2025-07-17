#include <ESP8266WiFi.h>

void setup()
{
  Serial.begin(115200);
  Serial.println();

  WiFi.begin("MIFON", "");

  Serial.print("Connecting To The WIFI");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected To The WIFI, IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {}

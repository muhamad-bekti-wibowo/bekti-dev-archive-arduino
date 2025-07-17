#include <ESP8266WiFi.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "DHT.h" 
#define DHTPIN 5
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
dht.begin();
}

void loop() {
  Serial.print("temperature : ");
  Serial.println(dht.readTemperature());
  Serial.print("humidity : ");
  Serial.println(dht.readHumidity());
  delay(1000);
}

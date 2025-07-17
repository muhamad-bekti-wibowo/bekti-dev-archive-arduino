#include <Wire.h>
#include <BH1750.h>
#include <Arduino.h>
BH1750 lightMeter(0x23);
void setup() {
#define GND 13
#define VCC 2
#define Addres 13
  pinMode(GND, OUTPUT);
  pinMode(VCC, OUTPUT);
  pinMode(Addres, OUTPUT);
  digitalWrite(Addres, LOW);
  digitalWrite(GND, LOW);
  digitalWrite(VCC, HIGH);
  Serial.begin(115200);
  
   delay(1000);
  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    Serial.println(F("BH1750 Advanced begin"));
  }
  else {
    Serial.println(F("Error initialising BH1750"));
  }
}


void loop() {
  float lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
  delay(1000);
}

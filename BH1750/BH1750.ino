
#include <Wire.h>
#include <BH1750.h>
BH1750 lightMeter;
void setup() {
  Serial.begin(115200);
  lightMeter.begin();

}

void loop() {
  Serial.println("Tingkat Cahaya :");
  Serial.print(lightMeter.readLightLevel());
  Serial.println(" lux");
  delay(1000);
}

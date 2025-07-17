#include <AHT10.h>
AHT10 myAHT10(0x38);
void setup() {
  Serial.println("AHT10 test");
  Serial.begin(115200);
  Serial.println("AHT10 test");

  if (!myAHT10.begin()) {
    Serial.println("Couldn't find sensor!");
    while (1);
  }
}

void loop() {
  float temp = myAHT10.readTemperature();
    float rel_hum = myAHT10.readHumidity();
    Serial.print("Temp: "); Serial.print(temp); Serial.print(" C");
    Serial.print("\t\t");
    Serial.print("Humidity: "); Serial.print(rel_hum); Serial.println(" \%");
}

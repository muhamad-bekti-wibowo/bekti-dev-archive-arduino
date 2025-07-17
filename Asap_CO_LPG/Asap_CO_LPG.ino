#include <MQ2.h>
#include <Wire.h>

int sensorMQ2 = A0;
int lpg, co, asap;
MQ2 mq2(sensorMQ2);
void setup() {
  Serial.begin(9600);

  mq2.begin();

  Serial.print("Indomaker.com");
  delay(5000);
 
}
void loop() {
  float* values = mq2.read(true);
  lpg = mq2.readLPG();
  co = mq2.readCO();
  asap = mq2.readSmoke();
  Serial.print("Lpg:");
  Serial.print(lpg);
  Serial.print(" CO:");
  Serial.print(co);
  Serial.print("ASAP:");
  Serial.print(asap);
  Serial.println(" PPM");
  delay(1000);
}

#include <Wire.h>
#include <Adafruit_INA219.h>
// Adafruit_INA219 ina219; // jika menggunakan 1 modul ina219
Adafruit_INA219 ina219_A(0x40);
Adafruit_INA219 ina219_B(0x45);
float  tegangan, arus, shunt, daya;
void setup() {
  //ina219.begin();
  ina219_A.begin();
  ina219_B.begin();
  Serial.begin(9600);    
}
void loop() {
  tegangan = ina219_A.getBusVoltage_V ();
  shunt = ina219_A.getShuntVoltage_mV ();
  arus = ina219_A.getCurrent_mA ();
  daya = (tegangan + shunt )* arus ;
  Serial.print("Bus Voltage:   "); 
  Serial.print(tegangan); 
  Serial.println(" V");  
  
  Serial.print("Current:       "); 
  Serial.print(arus); 
  Serial.println(" mA");
  
  Serial.print("Power:         "); 
  Serial.print(daya); 
  Serial.println(" W");  
  
  Serial.println("");  
}






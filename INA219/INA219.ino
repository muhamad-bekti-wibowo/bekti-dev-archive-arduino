#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Adafruit_SPIDevice.h>
#include <Adafruit_INA219.h>


Adafruit_INA219 ina219;             //  Adafruit_INA219 ina219_B(0x45); tambahkan alamat dan variable jika menggunakan lebih dari 1 Modul INA219
float tegangan, shunt, arus, daya;  // menyatakan variable ini berisikan nilai ber koma

void setup(void) {
  ina219.begin();  // ganti ina219 sesuai dengan alamat
  Serial.begin(9600);
}

void loop(void) {
  tegangan = ina219.getBusVoltage_V();  // Medapatkan tegangan Vin -
  shunt = ina219.getShuntVoltage_mV();  // Mendapatkan tegangan pada resistor shunt
  arus = ina219.getCurrent_mA();        // Mendapatkan arus yang di lewati resistor shunt
  daya = ina219.getPower_mW();          // Mendapatkan power yang di lewati rangkaian tegangan x arus

  Serial.print("tegangan : ");
  Serial.print(tegangan);
  Serial.print(" arus : ");
  Serial.print(arus);
  Serial.print(" shunt : ");
  Serial.print(shunt);
  Serial.print(" daya : ");
  Serial.println(daya);
  delay(400);
}

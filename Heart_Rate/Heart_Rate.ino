#include <CircularBuffer.h>
#include <MAX30100.h>
#include <MAX30100_BeatDetector.h>
#include <MAX30100_Filters.h>
#include <MAX30100_PulseOximeter.h>
#include <MAX30100_Registers.h>
#include <MAX30100_SpO2Calculator.h>

//mendaftarkan Perpustakaan yang di gunakan
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <LiquidCrystal_PCF8574.h>
 
LiquidCrystal_PCF8574 lcd(0x27); 
//mendaftarkan batas waktu laporan
#define REPORTING_PERIOD_MS     1000
// Pulse Oximeter adalah antarmuka tingkat yang lebih tinggi ke sensor
// ia menawarkan:
// * pelaporan deteksi detak
// * perhitungan detak jantung
// * perhitungan SpO2 (tingkat oksidasi)

// Panggilan balik (terdaftar di bawah) diaktifkan ketika pulsa terdeteksi
PulseOximeter pox;
uint32_t tsLastReport = 0;
// kagak tau fungsinya buat apa
void onBeatDetected()
{
  Serial.println("Beat!");
}
void setup()
{ // menyambungkan ke komputer
  Serial.begin(115200);
  // tulis / print Initializing pulse oximeter..
  Serial.print("Initializing pulse oximeter..");
  // Inisialisasi instans Pulse Oximeter
  // Kegagalan umumnya disebabkan oleh kabel I2C yang tidak tepat, catu daya yang hilang
  // atau chip target yang salah
  if (!pox.begin()) {
    Serial.println("FAILED");
    for (;;);
  } else {
    Serial.println("SUCCESS");
  }
  /// Arus default untuk LED IR adalah 50mA dan dapat diubah
  // dengan menghapus komentar pada baris berikut. Periksa MAX30100 Registers.h untuk semua
  // opsi yang tersedia.
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
  // Daftarkan panggilan balik untuk deteksi ketukan
  pox.setOnBeatDetectedCallback(onBeatDetected);
  lcd.begin(16, 2); //prosedur pemanggilan LCD
   lcd.setBacklight(255);
}

void loop()
{ // Pastikan untuk menelepon pembaruan secepat mungkin
  pox.update();
  // Membuang detak jantung dan tingkat oksidasi secara asinkron ke serial
  // Untuk keduanya, nilai 0 berarti "tidak valid"
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    // tulis / print pada serial komunikasi
    Serial.print("Heart rate:");
    Serial.print(pox.getHeartRate());
    Serial.print("bpm / SpO2:");
    Serial.print(pox.getSpO2());
    Serial.println("%");
    // isi tsLastReport dengan millis
    tsLastReport = millis();
    lcd.clear(); 
    lcd.setCursor(0, 0);
    lcd.print("Heart rate:");
    lcd.print(pox.getHeartRate());
    lcd.setCursor(0, 1);
    lcd.print("bpm / SpO2:");
    lcd.print(pox.getSpO2());
    lcd.print("%");
    lcd.display();
  }
}

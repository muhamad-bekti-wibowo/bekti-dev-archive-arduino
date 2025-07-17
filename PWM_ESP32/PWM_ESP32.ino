#include <Arduino.h>

// Konfigurasi PWM
const int pwmPin = 10;         // Pin output PWM
const int pwmChannel = 0;     // Channel PWM (0-15 untuk ESP32)
const int pwmResolution = 8; // Resolusi PWM (1-16 bit)
const int pwmFrequency = 100000; // Frekuensi PWM 100 kHz

void setup() {
  // Konfigurasi PWM
  ledcSetup(pwmChannel, pwmFrequency, pwmResolution);
  ledcAttachPin(pwmPin, pwmChannel);
}

void loop() {
  // Duty cycle naik dari 0% ke 100%
  for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle++) {
    ledcWrite(pwmChannel, dutyCycle);
    delay(1000); // Delay 10 ms untuk melihat perubahan
  }

  // Duty cycle turun dari 100% ke 0%
  for (int dutyCycle = 255; dutyCycle >= 0; dutyCycle--) {
    ledcWrite(pwmChannel, dutyCycle);
    delay(1000); // Delay 10 ms untuk melihat perubahan
  }
}

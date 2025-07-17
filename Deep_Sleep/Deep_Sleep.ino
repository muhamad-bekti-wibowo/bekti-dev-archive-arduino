/*
   ESP8266 Deep sleep mode example
   Rui Santos
   Complete Project Details https://randomnerdtutorials.com
*/
void setup() {
  Serial.begin(115200);
  Serial.setTimeout(2000);

  // Wait for serial to initialize.
  while (!Serial) { }

  // Deep sleep mode for 30 seconds, the ESP8266 wakes up by itself when GPIO 16 (D0 in NodeMCU board) is connected to the RESET pin
  //Serial.println("I'm awake, but I'm going into deep sleep mode for 30 seconds");
  //ESP.deepSleep(30e6);
  pinMode(2, OUTPUT);
  // Deep sleep mode until RESET pin is connected to a LOW signal (for example pushbutton or magnetic reed switch)

}

void loop() {
  Serial.println("I'm awake, but I'm going into deep sleep mode until RESET pin is connected to a LOW signal");
  digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(2, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);

  // Serial.println("Proteksi Timer Aktif");

  unsigned long Timer_Sebelumnya;
  unsigned long Timer_Sekarang = millis();
  if (Timer_Sekarang - Timer_Sebelumnya >= 100000)
  {
    Timer_Sebelumnya = millis();
    ESP.deepSleep(0);
  }
}

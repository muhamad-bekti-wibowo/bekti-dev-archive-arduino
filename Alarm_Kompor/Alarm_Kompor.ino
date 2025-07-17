uint64_t PM;
void setup() {
  pinMode(7, OUTPUT);
}

void loop() {
  digitalWrite(7, digitalRead(2));
  if ( millis() - PM >= 30000) {
    PM = millis();
    digitalWrite(7, 1);
    delay(10000);
    digitalWrite(7, 0);
  }
}

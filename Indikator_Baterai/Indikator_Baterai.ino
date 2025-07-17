void setup() {
  Serial.begin(115200);  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
}

void loop() {
  int  voltagebatt = analogRead(A0) * (5000 / 1023.0);
  Serial.println(voltagebatt);


  switch (map(voltagebatt, 3200, 4200, 0, 5)) {
    case 0:    // your hand is on the sensor
      digitalWrite(2, 0);
      digitalWrite(3, 0);
      digitalWrite(4, 0);
      digitalWrite(5, 0);
      digitalWrite(6, 0);
      break;
    case 1:    // your hand is close to the sensor
      digitalWrite(2, 0);
      digitalWrite(3, 0);
      digitalWrite(4, 0);
      digitalWrite(5, 0);
      digitalWrite(6, 1);
      break;
    case 2:    // your hand is a few inches from the sensor
      digitalWrite(2, 0);
      digitalWrite(3, 0);
      digitalWrite(4, 0);
      digitalWrite(5, 1);
      digitalWrite(6, 1);
      break;
    case 3:    // your hand is nowhere near the sensor
      digitalWrite(2, 0);
      digitalWrite(3, 0);
      digitalWrite(4, 1);
      digitalWrite(5, 1);
      digitalWrite(6, 1);
      break;
    case 4:    // your hand is nowhere near the sensor
      digitalWrite(2, 0);
      digitalWrite(3, 1);
      digitalWrite(4, 1);
      digitalWrite(5, 1);
      digitalWrite(6, 1);
      break;
    case 5:    // your hand is nowhere near the sensor
      digitalWrite(2, 1);
      digitalWrite(3, 1);
      digitalWrite(4, 1);
      digitalWrite(5, 1);
      digitalWrite(6, 1);
      break;
  }
  delay(10);
}

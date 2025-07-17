const int pirPin = 4;
const int LED = 2;
int pirState = LOW;
int counter = 0;

// Penanda waktu
unsigned long previousMillisIncrement = 0;
unsigned long previousMillisDecrement = 0;

int lastState = LOW;
int currentState = LOW;

unsigned long lastChangeMillis = 0;
unsigned long totalOnTime = 0;
unsigned long totalOffTime = 0;

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  currentState = digitalRead(pirPin);

  unsigned long currentMillis = millis();

  if (currentState != lastState) {
    // Ada perubahan status
    unsigned long duration = currentMillis - lastChangeMillis;

    if (lastState == HIGH) {
      totalOnTime += duration;
      Serial.print(digitalRead(pirPin));
      Serial.print("Durasi ON: ");
      Serial.print(duration / 1000.0);
      Serial.println(" detik");
    } else {
      totalOffTime += duration;
      Serial.print(digitalRead(pirPin));
      Serial.print("Durasi OFF: ");
      Serial.print(duration / 1000.0);
      Serial.println(" detik");
    }

    // Update penanda
    lastState = currentState;
    lastChangeMillis = currentMillis;
  }
  pirState = digitalRead(pirPin);

  unsigned long currentMilliss = millis();

  if (pirState == HIGH) {
    // Saat PIR aktif
    if (currentMilliss - previousMillisIncrement >= 100) {
      previousMillisIncrement = currentMilliss;

      if (counter < 100) {
        counter++;
      }
    }

    // Reset decrement timer supaya tidak langsung turun saat sensor OFF
    previousMillisDecrement = currentMilliss;
  } else {
    // Saat PIR tidak aktif
    if (currentMilliss - previousMillisDecrement >= 1000) {
      previousMillisDecrement = currentMilliss;

      if (counter > 0) {
        counter--;
      }
    }
  }

  if (counter > 10) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
}

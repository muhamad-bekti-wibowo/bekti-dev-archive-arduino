#define GND 7
#define echoPin 6
#define trigPin 5
#define VCC 4
#define LEDPin 13

long duration, distance;

void setup() {
  Serial.begin (115200);

  pinMode(GND, OUTPUT);
  pinMode(VCC, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LEDPin, OUTPUT);

  digitalWrite(GND, LOW);
  digitalWrite(VCC, HIGH);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);                                
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2;
  Serial.print(distance);
  Serial.println("cm");
}

bool saklarlock;
int saklar;
void setup() {
  Serial.begin(115200);
  pinMode(A0, INPUT);
}

void loop() {
  if (!saklarlock) {
    if (analogRead(A0)<850 && analogRead(A0)>700) {saklar = 1;}
    if (analogRead(A0)<700 && analogRead(A0)>500) {saklar = 2;}
    if (analogRead(A0)<350 && analogRead(A0)>200) {saklar = 3;}
    Serial.println(saklar);
    Serial.print("sensor = ");
  Serial.println(analogRead(A0));
  }
  if (analogRead(A0)< 100) {saklar = 0;  }
  if (!saklar) {saklarlock = 0;}
  else  {if (saklarlock) {saklar  = 10;}}

   

   if (saklar > 0)  {
    if (!saklarlock)    {
      saklarlock = 1;
    }
  }
}

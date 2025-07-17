int a=1000 ;
int b=10000 ;
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);


}

// the loop routine runs over and over again forever:
void loop() {
//11
  digitalWrite(2, 0) ; //Hijau2
  digitalWrite(3, 0); //oren2
  digitalWrite(4, 1) ; //mera2
  digitalWrite(5, 0) ; //Hijau3
  digitalWrite(6, 0) ; //oren3
  digitalWrite(7, 1); //merah3
  digitalWrite(8, 0) ; //Hijau4
  digitalWrite(9, 0) ; //oren4
  digitalWrite(10, 1) ; //merah4
  digitalWrite(11, 1); //Hijau1
  digitalWrite(12, 0) ; //oren1
  digitalWrite(13, 0) ; //merah1
  delay(b);
 digitalWrite(2, 0); //Hijau2
  digitalWrite(3, 1); //oren2
  digitalWrite(4, 0); //mera2
  digitalWrite(5, 0) ; //Hijau3
  digitalWrite(6, 0) ; //oren3
  digitalWrite(7, 1); //merah3
  digitalWrite(8, 0) ; //Hijau4
  digitalWrite(9, 0) ; //oren4
  digitalWrite(10, 1) ; //merah4
  digitalWrite(11, 1); //Hijau1
  digitalWrite(12, 0) ; //oren1
  digitalWrite(13, 0) ; //merah1
  delay(a);
  digitalWrite(2, 1); //Hijau2
  digitalWrite(3, 0); //oren2
  digitalWrite(4, 0); //mera2
  digitalWrite(5, 0) ; //Hijau3
  digitalWrite(6, 0) ; //oren3
  digitalWrite(7, 1); //merah3
  digitalWrite(8, 0) ; //Hijau4
  digitalWrite(9, 0) ; //oren4
  digitalWrite(10, 1) ; //merah4
  digitalWrite(11, 0); //Hijau1
  digitalWrite(12, 0) ; //oren1
  digitalWrite(13, 1) ; //merah1
  delay(b);
 digitalWrite(2, 1); //Hijau2
  digitalWrite(3, 0); //oren2
  digitalWrite(4, 0); //mera2
  digitalWrite(5, 0) ; //Hijau3
  digitalWrite(6, 1) ; //oren3
  digitalWrite(7, 0); //merah3
  digitalWrite(8, 0) ; //Hijau4
  digitalWrite(9, 0) ; //oren4
  digitalWrite(10, 1) ; //merah4
  digitalWrite(11, 0); //Hijau1
  digitalWrite(12, 0) ; //oren1
  digitalWrite(13, 1) ; //merah1
delay(a);
  digitalWrite(2, 0); //Hijau2
  digitalWrite(3, 0); //oren2
  digitalWrite(4, 1); //mera2
  digitalWrite(5, 1) ; //Hijau3
  digitalWrite(6, 0) ; //oren3
  digitalWrite(7, 0); //merah3
  digitalWrite(8, 0) ; //Hijau4
  digitalWrite(9, 0) ; //oren4
  digitalWrite(10, 1) ; //merah4
  digitalWrite(11, 0); //Hijau1
  digitalWrite(12, 0) ; //oren1
  digitalWrite(13, 1) ; //merah1
  delay(b);
   digitalWrite(2, 0); //Hijau2
  digitalWrite(3, 0); //oren2
  digitalWrite(4, 1); //mera2
  digitalWrite(5, 1) ; //Hijau3
  digitalWrite(6, 0) ; //oren3
  digitalWrite(7, 0); //merah3
  digitalWrite(8, 0) ; //Hijau4
  digitalWrite(9, 1) ; //oren4
  digitalWrite(10, 0) ; //merah4
  digitalWrite(11, 0); //Hijau1
  digitalWrite(12, 0) ; //oren1
  digitalWrite(13, 1) ; //merah1
delay(a);

  digitalWrite(2, 0); //Hijau2
  digitalWrite(3, 0); //oren2
  digitalWrite(4, 1); //mera2
  digitalWrite(5, 0) ; //Hijau3
  digitalWrite(6, 0) ; //oren3
  digitalWrite(7, 1); //merah3
  digitalWrite(8, 1) ; //Hijau4
  digitalWrite(9, 0) ; //oren4
  digitalWrite(10, 0) ; //merah4
  digitalWrite(11, 0); //Hijau1
  digitalWrite(12, 0) ; //oren1
  digitalWrite(13, 1) ; //merah1
  delay(b);
   digitalWrite(2, 0); //Hijau2
  digitalWrite(3, 0); //oren2
  digitalWrite(4, 1); //mera2
  digitalWrite(5, 0) ; //Hijau3
  digitalWrite(6, 0) ; //oren3
  digitalWrite(7, 1); //merah3
  digitalWrite(8, 1) ; //Hijau4
  digitalWrite(9, 0) ; //oren4
  digitalWrite(10, 0) ; //merah4
  digitalWrite(11, 0); //Hijau1
  digitalWrite(12, 1) ; //oren1
  digitalWrite(13, 0) ; //merah1
delay(a);
}

#include <IRremote.h>

int RECV_PIN = 15;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(115200);
  irrecv.enableIRIn(); // Start the receiver
}

void loop()
{
  if (irrecv.decode(&results))
  {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
  if (irrecv.decode(&results))  // jalankan jika ada data masuk
  {
    Serial.println(results.value);
    long data = results.value; // simpan data di variabel data
    irrecv.resume();


  }
}

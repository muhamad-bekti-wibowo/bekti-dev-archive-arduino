#include <ESP8266WiFi.h>
#include <espnow.h>
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

SoftwareSerial mySerial(2, 14); // RX, TX
//uint8_t broadcastAddress[] = {0xe8, 0xdb, 0x84, 0xc4, 0x76, 0x1e};
uint8_t broadcastAddress[] = {0xac, 0x0b, 0xfb, 0xdb, 0x28, 0x97};


String condition;
String incomingcondition;
const long interval = 1000;
unsigned long previousMillis = 0;
String success;
int motor;
typedef struct struct_message {
  String condition;
} struct_message;

struct_message Readings;
struct_message incomingReadings;

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (!sendStatus) {
    Serial.println("Delivery success");
    if (motor < 10) {
      motor++;
    }
  }
  else {
    if (motor > 0) {
      motor--;
    }
    Serial.println("Delivery fail");
  }
}

void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  Serial.print("Bytes received: ");
  Serial.println(len);
  incomingcondition = incomingReadings.condition;
  incomingReadings.condition == "";
}


void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
  esp_now_register_send_cb(OnDataSent);
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
  esp_now_register_recv_cb(OnDataRecv);
  mySerial.begin (9600);
  mp3_set_serial (mySerial);  //set softwareSerial for DFPlayer-mini mp3 module
  delay(1);  //wait 1ms for mp3 module to set volume
  mp3_set_volume (15);

}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    condition = "OK";
    Readings.condition = condition; // procecing
    esp_now_send(broadcastAddress, (uint8_t *) &Readings, sizeof(Readings)); //send
    Serial.print(incomingcondition);

    if (motor > 3) {
      digitalWrite(2, 1);
      mp3_play(2);
      delay (2000);
    }
    else {
      digitalWrite(2, 0);
      mp3_play(1);
      delay (2000);
    }

  }
}

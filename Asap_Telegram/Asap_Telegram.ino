#include <MQ2.h>
int pinAout = A0;
int lpg_gas, co_gas, smoke_gas; 
MQ2 mq2(pinAout);

#include <Wire.h>

const int sensor_gas = 12;
const int buzzer = D6;
bool krmTele = false;

#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>   
#include <ArduinoJson.h>
const char* ssid = "MIFON";
const char* password = "";
String wifiConf[3];

#define BOTtoken "6927145290:AAGwuHiNRG0731oyEoE0WqTWiE0YoDUVgVc"  //Token/API botFather
#define CHAT_ID "6737460102" //@idbot

#ifdef ESP8266
  X509List cert(TELEGRAM_CERTIFICATE_ROOT);
#endif

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

void setup()
{
  Serial.begin(9600);
  while(!Serial);  
  mq2.begin();
  Serial.println("||***************** PERSIAPAN SISTEM *****************||");
  
  pinMode(sensor_gas,INPUT);
  pinMode(buzzer,OUTPUT);

  #ifdef ESP8266
    configTime(0, 0, "pool.ntp.org"); 
    client.setTrustAnchors(&cert); 
  #endif

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  #ifdef ESP32
    client.setCACert(TELEGRAM_CERTIFICATE_ROOT); 
  #endif
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println(WiFi.localIP());  
  delay(2500);
}
void readMQ2(){
  float* values= mq2.read(true);//tampil pembacaan di serial Monitor 
  
  lpg_gas = mq2.readLPG();
  co_gas = mq2.readCO();
  smoke_gas = mq2.readSmoke();  
  
}
void loop()
{ 
  readMQ2();
  //if (lpg_gas > 200){
  //  digitalWrite(buzzer,HIGH);
  //  if(!krmTele){
      bot.sendMessage(CHAT_ID, "Terjadi kebocoran gas dengan nilai " + (String)lpg_gas + " ppm", "");
  //    krmTele = true;
 //   }
 // }
 // else{
 //   digitalWrite(buzzer,LOW);
 //   krmTele = false;
 // }
  delay(1000);
}

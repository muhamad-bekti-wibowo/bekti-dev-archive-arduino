/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-esp8266-web-server-outputs-momentary-switch/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#else
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>



// REPLACE WITH YOUR NETWORK CREDENTIALS
const char* ssid     = "HUAWEI-E473";
const char* password = "qpJqq97n";
const int output = 16;
const int output1 = 5;
const int output2 = 4;
const int output3 = 0;
// HTML web page
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
  <head>
    <title>WEB Server Joystik</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
    button{
    border: none;
    padding: 13px 17px;
    border-radius: 10px;
   font-family:&#39;Muli&#39;, sans-serif;
    color: white;
    display: inline-block;
    cursor: pointer;
    text-decoration: none;
    }
    .warna{background-color: #498CFB;}
    .warna1{background-color: #FF2867;}
    .warna2{background-color: #28BF7B;}
    .warna3{background-color: #FF2047;}
    .warna4{background-color: #E58F16;} 
    button:hover{
      background-color: #333;
      }
      h1{color: aqua;} 
      </style>
      </head>
      <body>
      <h1>WEB Server Joystik</h1>
      <button class="warna" onmousedown="toggleCheckbox('on');" ontouchstart="toggleCheckbox('on');" onmouseup="toggleCheckbox('off');" ontouchend="toggleCheckbox('off');">.Atas.</button></br></br>
   <button class="warna1" onmousedown="toggleCheckbox('on1');" ontouchstart="toggleCheckbox('on1');" onmouseup="toggleCheckbox('off1');" ontouchend="toggleCheckbox('off1');">.Kiri......</button>
   <button class="warna2" onmousedown="toggleCheckbox('on2');" ontouchstart="toggleCheckbox('on2');" onmouseup="toggleCheckbox('off2');" ontouchend="toggleCheckbox('off2');">.Kanan. </button></br></br>
   <button class="warna3" onmousedown="toggleCheckbox('on3');" ontouchstart="toggleCheckbox('on3');" onmouseup="toggleCheckbox('off3');" ontouchend="toggleCheckbox('off3');">.Bawah. </button></br>
   
   <script>
   function toggleCheckbox(x) {
     var xhr = new XMLHttpRequest();
     xhr.open("GET", "/" + x, true);
     xhr.send();
   }
  </script>

  </body>
</html>)rawliteral";
int a,b,c,d;
void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed!");
    return;
  }
  Serial.println();
  Serial.print("ESP IP Address: http://");
  Serial.println(WiFi.localIP());

  pinMode(output, OUTPUT);
  digitalWrite(output, 1);
  pinMode(output1, OUTPUT);
  digitalWrite(output1, 1);
  pinMode(output2, OUTPUT);
  digitalWrite(output2, 1);
  pinMode(output3, OUTPUT);
  digitalWrite(output3, 1);
  // Send web page to client
 server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

    // Receive an HTTP GET request
  server.on("/on", HTTP_GET, [] (AsyncWebServerRequest * request) {
  a= 1;
  
    request->send(200, "text/plain", "ok");
  });
  // Receive an HTTP GET request
  server.on("/off", HTTP_GET, [] (AsyncWebServerRequest * request) { 
  a= 0;
    request->send(200, "text/plain", "ok");
  });
  
server.on("/on1", HTTP_GET, [] (AsyncWebServerRequest * request) {
     
  b=1;
    request->send(200, "text/plain", "ok");
  });

  // Receive an HTTP GET request
  server.on("/off1", HTTP_GET, [] (AsyncWebServerRequest * request) {
   b=0;
   request->send(200, "text/plain", "ok");
  });
  
server.on("/on2", HTTP_GET, [] (AsyncWebServerRequest * request) {
   c=1;
   
    request->send(200, "text/plain", "ok");
  });

  // Receive an HTTP GET request
  server.on("/off2", HTTP_GET, [] (AsyncWebServerRequest * request) {
  c=0;
  request->send(200, "text/plain", "ok");
  });
  
  server.on("/on3", HTTP_GET, [] (AsyncWebServerRequest * request) {
  d=1;

  request->send(200, "text/plain", "ok");
  });

  // Receive an HTTP GET request
  server.on("/off3", HTTP_GET, [] (AsyncWebServerRequest * request) {
   d=0;
    request->send(200, "text/plain", "ok");
  });





  
  server.onNotFound(notFound);
  server.begin();
}

void loop() {
if(a==1){
  digitalWrite(output,1);
   digitalWrite(output1,0);
   digitalWrite(output2,1);
   digitalWrite(output3,0);
  }
 else  if(a==0 && b == 0&&c==0 && d==0){
  digitalWrite(output,1);
   digitalWrite(output1,1);
   digitalWrite(output2,1);
   digitalWrite(output3,1);
  }
 else  if(b==1){
  digitalWrite(output,1);
   digitalWrite(output1,1);
   digitalWrite(output2,0);
   digitalWrite(output3,1);
  }
 else if(c==1){
  digitalWrite(output,1);
   digitalWrite(output1,0);
   digitalWrite(output2,1);
   digitalWrite(output3,1);
  }
  else if (d==1){
    digitalWrite(output,0);
   digitalWrite(output1,1);
   digitalWrite(output2,0);
   digitalWrite(output3,1);
  }

   
}

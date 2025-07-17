#include "painlessMesh.h"
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

// MESH Configuration
#define MESH_PREFIX     "MESH-LAMPU"
#define MESH_PASSWORD   "12345678"
#define MESH_PORT       56789

Scheduler userScheduler; // to control your personal task
painlessMesh  mesh;

#define LED_BUILTIN 2 // Sesuaikan dengan pin LED build-in perangkat Anda
bool state;

// WiFi Configuration
const char* ssid = "MIFON";
const char* password = "";

AsyncWebServer server(80);

// User stub
void sendMessage(); // Prototype so PlatformIO doesn't complain

Task taskSendMessage(TASK_SECOND * 1, TASK_FOREVER, &sendMessage);

void sendMessage() {
  String msg = "PUSAT:" + String(state); // Kirim pesan kontrol LED
  mesh.sendBroadcast(msg);
  taskSendMessage.setInterval(random(TASK_SECOND * 1, TASK_SECOND * 5));
}

// Needed for painless library
void receivedCallback(uint32_t from, String &msg) {
  Serial.printf("Received from %u msg=%s\n", from, msg.c_str());
}

void newConnectionCallback(uint32_t nodeId) {
  Serial.printf("--> New Connection, nodeId = %u\n", nodeId);
}

void changedConnectionCallback() {
  Serial.printf("Changed connections\n");
}

void nodeTimeAdjustedCallback(int32_t offset) {
  Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(), offset);
}

void setup() {
  Serial.begin(115200);

  // Default LED mati
  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH); // LED mati (aktif rendah)
  digitalWrite(0, HIGH);

  // WiFi setup
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());

  // Web server routes
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    String html = "<html><body>";
    html += "<h1>Kontrol LED</h1>";
    html += "<button onclick=\"fetch('/lampu/on')\">LED ON</button>";
    html += "<button onclick=\"fetch('/lampu/off')\">LED OFF</button>";
    html += "<script>function fetch(url){const x=new XMLHttpRequest();x.open('GET',url,true);x.send();}</script>";
    html += "</body></html>";
    request->send(200, "text/html", html);
  });

  server.on("/lampu/on", HTTP_GET, [](AsyncWebServerRequest *request) {
    state = true;
    digitalWrite(2, LOW); // HIDUPKAN LED (LOW karena aktif rendah)
    digitalWrite(0, LOW);
    String msg = "PUSAT:" + String(state);
    mesh.sendBroadcast(msg);
    request->send(200, "text/plain", "LED ON");
  });

  server.on("/lampu/off", HTTP_GET, [](AsyncWebServerRequest *request) {
    state = false;
    digitalWrite(2, HIGH); // MATIKAN LED
    digitalWrite(0, HIGH);
    String msg = "PUSAT:" + String(state);
    mesh.sendBroadcast(msg);
    request->send(200, "text/plain", "LED OFF");
  });

  server.begin();

  // Mesh setup
  WiFi.mode(WIFI_STA);
  mesh.setDebugMsgTypes(ERROR | STARTUP);  // set before init() so that you can see startup messages
  mesh.init(MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT);
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);

  userScheduler.addTask(taskSendMessage);
  taskSendMessage.enable();
}

void loop() {
  mesh.update();
}

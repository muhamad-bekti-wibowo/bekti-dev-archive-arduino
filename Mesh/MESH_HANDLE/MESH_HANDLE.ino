#include "painlessMesh.h"

#define   MESH_PREFIX     "MESH-LAMPU"
#define   MESH_PASSWORD   "12345678"
#define   MESH_PORT       56789

painlessMesh  mesh;
bool state;
void receivedCallback(uint32_t from, String &msg) {
  Serial.printf("Received from %u msg=%s\n", from, msg.c_str());
  if (msg.indexOf("08:F9:E0:6C:44:57:1") != -1) {
    digitalWrite(2, LOW); // HIDUPKAN LED (LOW karena LED build-in aktif rendah)
    digitalWrite(0, LOW);
    Serial.println("LED ON");
  } else if (msg.indexOf("08:F9:E0:6C:44:57:0") != -1) {
    digitalWrite(2, HIGH); // MATIKAN LED
    digitalWrite(0, HIGH);
    Serial.println("LED OFF");
  }
  else if (msg.indexOf("ALL:0") != -1) {
    digitalWrite(2, 1); // MATIKAN LED
    digitalWrite(0, 1);
    Serial.println("LED OFF");
  }
  else if (msg.indexOf("ALL:1") != -1) {
    digitalWrite(2, 0); // MATIKAN LED
    digitalWrite(0, 0);
    Serial.println("LED ON");
  }
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
  pinMode(0, OUTPUT);
  // Inisialisasi LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  WiFi.mode(WIFI_OFF);
  mesh.setDebugMsgTypes(ERROR);

  mesh.init(MESH_PREFIX, MESH_PASSWORD, MESH_PORT);
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);
}

void loop() {
  mesh.update();
}

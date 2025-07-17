#include "painlessMesh.h"
//PUSAT

#define   MESH_PREFIX     "MESH-LAMPU"
#define   MESH_PASSWORD   "12345678"
#define   MESH_PORT       56789

unsigned long previousMillis = 0;
const long interval = 10000;

painlessMesh  mesh;
String deviceID = "A4:CF:12:FA:E1:29";
#define LED_BUILTIN 2
bool state;
// User stub
String lastString;
// Needed for painless library
void receivedCallback(uint32_t from, String &msg) {
  Serial.printf("Received from %u msg=%s\n", from, msg.c_str());
  if (msg.indexOf("A4:CF:12:FA:E1:29:1") != -1) {
    digitalWrite(2, LOW); // HIDUPKAN LED (LOW karena LED build-in aktif rendah)
    digitalWrite(0, LOW);
    Serial.println("LED ON");
  } else if (msg.indexOf("A4:CF:12:FA:E1:29:0") != -1) {
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
  Serial.begin(9600);
  // Default LED mati
  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);
  WiFi.mode(WIFI_OFF);
  mesh.setDebugMsgTypes(ERROR | MESH_STATUS | CONNECTION | SYNC | COMMUNICATION | GENERAL | MSG_TYPES | REMOTE);

  mesh.init(MESH_PREFIX, MESH_PASSWORD, MESH_PORT);
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);

}

void loop() {
  if (Serial.available())
  {
    String in = Serial.readStringUntil('\r');
    if (in == deviceID)  {
      state = !state;
      digitalWrite(2, !state);
      digitalWrite(0, !state);
    }
    else if (in.indexOf(deviceID + ":0") != -1) {
      state = 0;
      digitalWrite(2, !state);
      digitalWrite(0, !state);
    }
    else if (in.indexOf(deviceID + ":1") != -1) {
      state = 1;
      digitalWrite(2, !state);
      digitalWrite(0, !state);
    }
    else if (in.indexOf("ALL:0") != -1) {
      digitalWrite(2, 1); 
      digitalWrite(0, 1);
      Serial.println("LED OFF");
    }
    else if (in.indexOf("ALL:1") != -1) {
      digitalWrite(2, 0); 
      digitalWrite(0, 0);
      Serial.println("LED ON");
    }
    mesh.sendBroadcast(in);
    lastString = in ;
    Serial.println(in);
  }

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    mesh.sendBroadcast(lastString);
  }
  mesh.update();
}

#include <ESP8266WiFi.h>

#include <EEEPROM.h>

#include "index.h"
#include <split.h>
#include <wifi_available.h>

#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

EEEPROM EEEPROM(512);  // Inisialisasi objek EEEPROM dengan ukuran 512 byte

AsyncWebServer server(80);  // Membuat server web yang berjalan pada port 80

int adrress = 100;  // Mendefinisikan alamat EEPROM untuk menyimpan data
bool esprestart;  // Variabel untuk mengontrol restart ESP

// Fungsi untuk menangani permintaan yang tidak ditemukan (404)
void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setup() {
  Serial.begin(115200);  // Memulai komunikasi serial dengan baud rate 115200
  WiFi.mode(WIFI_AP_STA);  // Mengatur ESP dalam mode Access Point (AP) dan Station (STA)
  WiFi.disconnect();  // Memutuskan sambungan WiFi jika ada yang tersambung sebelumnya
  delay(100);  // Memberikan delay 100ms

  // Membaca SSID dan Password dari EEPROM dan memisahkannya berdasarkan koma
  String SSID_Password = EEEPROM.readString(0, EEEPROM.value(adrress));
  String* data = split(SSID_Password, ',');

  // Jika WiFi yang disimpan tersedia, hubungkan ke jaringan tersebut
  if (wifi_available(data[0])) {
    WiFi.mode(WIFI_STA);  // Mengatur ESP dalam mode Station (STA)
    WiFi.disconnect();  // Memutuskan sambungan WiFi yang ada
    WiFi.begin(data[0], data[1]);  // Memulai koneksi WiFi dengan SSID dan password yang disimpan
    Serial.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("\nConnected to WiFi.");  // Menampilkan pesan bahwa koneksi berhasil
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());  // Menampilkan alamat IP ESP di jaringan
  }
  else
  {
    // Jika WiFi tidak tersedia, buat Access Point dengan nama acak
    randomSeed(random(0, 10000));
    String randomChars;
    for (int i = 0; i < 10; i++) {
      randomChars += random(0, 2) == 0 ? (char)random('A', 'Z' + 1) : (char)random('a', 'z' + 1);
    }
    WiFi.softAP(randomChars);  // Memulai Access Point dengan nama acak
    Serial.println("\nAccess Point started. " + randomChars);
    Serial.print("AP IP Address: ");
    Serial.println(WiFi.softAPIP());  // Menampilkan alamat IP dari Access Point
  }
  // Mengatur rute web server untuk menangani permintaan HTTP GET di root "/"
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/html", Configuration);
  });

  // Mengatur rute web server untuk menangani permintaan HTTP POST di "/ssid_password"
  server.on("/ssid_password", HTTP_POST, [] (AsyncWebServerRequest * request) {
    String message;
    if (request->hasParam("ssid", true)) {
      message = request->getParam("ssid", true)->value();  // Mendapatkan nilai SSID dari parameter POST
    }
    if (request->hasParam("pass", true)) {
      message += "," + request->getParam("pass", true)->value();  // Mendapatkan nilai Password dari parameter POST
    }
    EEEPROM.writeString( message, 0, adrress);  // Menyimpan SSID dan Password ke EEPROM
    esprestart = 1;  // Mengatur variabel untuk merestart ESP
    request->send(200, "text/plain", ("SSID dan Password telah diganti dengan " + message).c_str());
  });

  server.onNotFound(notFound);  // Mengatur handler untuk permintaan yang tidak ditemukan
  server.begin();  // Memulai web server

}

void loop() {
  if (esprestart) {
    delay(5000);  // Memberikan delay 5 detik sebelum restart
    ESP.restart();  // Merestart ESP
  }
}

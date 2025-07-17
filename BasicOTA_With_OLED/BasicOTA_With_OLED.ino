#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#ifndef STASSID
#define STASSID "MIFON"
#define STAPSK ""
#endif

// OLED Display Configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1  // Reset pin not used on most OLED displays
#define SCREEN_ADDRESS 0x3C  // Common I2C address for SSD1306 OLED displays

// Initialize the OLED display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char* ssid = STASSID;
const char* password = STAPSK;

// Custom function to print to both Serial and OLED
void printToSerialAndDisplay(String message) {
  Serial.println(message);
  
  // Print to display
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(message);
  display.display();
}

void setup() {
  Serial.begin(115200);
  Serial.println("Booting");
  
  // Initialize OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("SSD1306 allocation failed");
    for(;;); // Don't proceed if OLED initialization fails
  }
  
  // Show initial message
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Booting...");
  display.display();
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    printToSerialAndDisplay("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  
  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);
  
  // Hostname defaults to esp8266-[ChipID]
  // ArduinoOTA.setHostname("myesp8266");
  
  // No authentication by default
  // ArduinoOTA.setPassword("admin");
  
  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");
  
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else {  // U_FS
      type = "filesystem";
    }
    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    String message = "Start updating " + type;
    Serial.println(message);
    
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println(message);
    display.display();
  });
  
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
    
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Update complete!");
    display.display();
  });
  
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    int percentComplete = (progress / (total / 100));
    Serial.printf("Progress: %u%%\r", percentComplete);
    
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Updating: ");
    display.print(percentComplete);
    display.println("%");
    
    // Draw a progress bar
    display.drawRect(0, 20, 100, 10, WHITE);
    display.fillRect(0, 20, percentComplete, 10, WHITE);
    display.display();
  });
  
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Error: ");
    
    String errorMsg;
    if (error == OTA_AUTH_ERROR) {
      errorMsg = "Auth Failed";
    } else if (error == OTA_BEGIN_ERROR) {
      errorMsg = "Begin Failed";
    } else if (error == OTA_CONNECT_ERROR) {
      errorMsg = "Connect Failed";
    } else if (error == OTA_RECEIVE_ERROR) {
      errorMsg = "Receive Failed";
    } else if (error == OTA_END_ERROR) {
      errorMsg = "End Failed";
    }
    
    Serial.println(errorMsg);
    display.println(errorMsg);
    display.display();
  });
  
  ArduinoOTA.begin();
  
  String readyMsg = "Ready";
  printToSerialAndDisplay(readyMsg);
  
  String ipMsg = "IP: " + WiFi.localIP().toString();
  display.setCursor(0, 10);
  display.println(ipMsg);
  display.display();
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  ArduinoOTA.handle();
  // Additional code can be added here
}

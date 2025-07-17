#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // Lebar layar OLED (pixel)
#define SCREEN_HEIGHT 64  // Tinggi layar OLED (pixel)

// Inisialisasi objek display SSD1306
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int buttonPin = 13;
int counter = 0;
unsigned long pressDuration;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  pinMode(buttonPin, INPUT_PULLUP);  // Set pin tombol sebagai input dengan pull-up resistor
  pinMode(2, OUTPUT);
  digitalWrite(2,0);
}

void loop() {
  
  if (!digitalRead(buttonPin)) {
    unsigned long startTime = millis();
    while (!digitalRead(buttonPin)) {
      delay(10);
      pressDuration = millis() - startTime;
      if (pressDuration > 500) {
        while (!digitalRead(buttonPin)) {
          pressDuration = millis() - startTime;
          delay(20);  // Delay untuk stabilitas
          counter += 1;  // Tambah 1 ke counter
          Serial.print("Nilai counter: ");
          Serial.println(counter);
          display.clearDisplay();
          display.setTextColor(WHITE);
          display.setTextSize(4);
          display.setCursor(random(0,128/4), random(0,64/2));
          display.print(counter);
          display.display();
          digitalWrite(2,!digitalRead(2));
        }
      }
    }
    counter += 1;
    Serial.print("Nilai counter: ");
    Serial.println(counter);
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(4);
    display.setCursor(0, 0);
    display.print(counter);
    display.display();
    digitalWrite(2,!digitalRead(2));
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(4);
  display.setCursor(0, 0);
  display.print(counter);
  display.display();
}

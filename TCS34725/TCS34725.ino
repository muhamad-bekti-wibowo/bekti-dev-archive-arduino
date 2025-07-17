#include <Adafruit_TCS34725.h>
#include "Wire.h"
#include "ColorConverterLib.h"

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_240MS, TCS34725_GAIN_16X);

struct Color {
  const char* name;
  int r;
  int g;
  int b;
};

// Daftar warna yang umum
Color colors[] = {
  { "Dark Slate Gray", 54, 93, 111 },
  { "Red", 255, 0, 0 },
  { "Green", 0, 255, 0 },
  { "Blue", 0, 0, 255 },
  { "Cyan", 0, 255, 255 },
  { "Magenta", 255, 0, 255 },
  { "Yellow", 255, 255, 0 },
  { "Black", 0, 0, 0 },
  { "White", 255, 255, 255 },
  { "Gray", 128, 128, 128 },
  { "Light Gray", 211, 211, 211 },
  { "Dark Gray", 169, 169, 169 },
  { "Orange", 255, 165, 0 },
  { "Purple", 128, 0, 128 },
  { "Pink", 255, 192, 203 },
  { "Brown", 165, 42, 42 },
  { "Lime", 0, 255, 0 },
  { "Teal", 0, 128, 128 },
  { "Navy", 0, 0, 128 },
  { "Olive", 128, 128, 0 },
  { "Coral", 255, 127, 80 },
  { "Salmon", 250, 128, 114 },
  { "Gold", 255, 215, 0 },
  { "Khaki", 240, 230, 140 },
  { "Plum", 221, 160, 221 },
  { "Lavender", 230, 230, 250 },
  { "Violet", 238, 130, 238 },
  { "Mint", 189, 252, 201 },
  { "Chocolate", 210, 105, 30 },
  { "Indigo", 75, 0, 130 },
  { "Dark Orange", 255, 140, 0 },
  { "Slate Blue", 106, 90, 205 },
  { "Firebrick", 178, 34, 34 },
  { "Sea Green", 46, 139, 87 },
  { "Medium Violet Red", 199, 21, 133 },
  { "Medium Sea Green", 60, 179, 113 },
  { "Light Blue", 173, 216, 230 },
  { "Steel Blue", 70, 130, 180 },
  { "Dark Salmon", 233, 150, 122 },
  { "Rosy Brown", 188, 143, 143 },
  { "Sky Blue", 135, 206, 235 },
  { "Deep Pink", 255, 20, 147 },
  { "Thistle", 216, 191, 216 },
  { "Medium Orchid", 186, 85, 211 },
  { "Sandy Brown", 244, 164, 96 }
};

// Fungsi untuk mencari nama warna berdasarkan nilai RGB
const char* rgbToColorName(int r, int g, int b) {
  int closestIndex = -1;
  float closestDistance = 1e6;  // Jarak terdekat yang sangat besar

  for (int i = 0; i < sizeof(colors) / sizeof(colors[0]); i++) {
    // Menghitung jarak Euclidean
    float distance = sqrt(pow(r - colors[i].r, 2) + pow(g - colors[i].g, 2) + pow(b - colors[i].b, 2));

    // Memperbarui warna terdekat jika jarak lebih kecil
    if (distance < closestDistance) {
      closestDistance = distance;
      closestIndex = i;
    }
  }

  // Mengembalikan nama warna terdekat
  if (closestIndex >= 0) {
    return colors[closestIndex].name;
  }
  return "Unknown Color";
}

void setup() {
  Serial.begin(9600);
  if (tcs.begin()) {
    //Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1)
      ;  // halt!
  }
}
int rgbtoGray(int r, int g, int b) {
  return (0.299 * r) + (0.587 * g) + (0.114 * b);
}

void loop() {

  float red, green, blue;
  tcs.setInterrupt(false);
  delay(50);
  tcs.getRGB(&red, &green, &blue);
  tcs.setInterrupt(true);
  red = red * 3.1875;
  green = green * 2.65625;
  blue = blue * 3.642857142857143;
  int R = int(red);
  int G = int(green);
  int B = int(blue);

  const char* colorName = rgbToColorName(red, green, blue);
  Serial.print("RGB: (");
  Serial.print(red);
  Serial.print(", ");
  Serial.print(green);
  Serial.print(", ");
  Serial.print(blue);
  Serial.print(") -> ");
  Serial.println(colorName);

  int grayValue = rgbtoGray(R, G, B);
  Serial.print("   rgbtoGray: ");
  Serial.print(int(grayValue));

  delay(1000);
}

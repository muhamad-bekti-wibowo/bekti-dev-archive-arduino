#include "BluetoothSerial.h"

// Periksa apakah Bluetooth tersedia
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth tidak tersedia atau tidak diaktifkan, aktifkan dengan menuconfig
#endif

BluetoothSerial SerialBT;

// Definisi pin motor
#define MOTOR_LEFT_PIN1 16  // Pin untuk motor kiri (arah 1)
#define MOTOR_LEFT_PIN2 17  // Pin untuk motor kiri (arah 2)
#define MOTOR_RIGHT_PIN1 18 // Pin untuk motor kanan (arah 1)
#define MOTOR_RIGHT_PIN2 19 // Pin untuk motor kanan (arah 2)

// Channel PWM
#define PWM_CHANNEL_LEFT1 0
#define PWM_CHANNEL_LEFT2 1
#define PWM_CHANNEL_RIGHT1 2
#define PWM_CHANNEL_RIGHT2 3

// Konfigurasi PWM
#define PWM_FREQ 5000      // Frekuensi PWM (5 kHz)
#define PWM_RESOLUTION 8   // Resolusi PWM (8-bit -> 0-255)

// Data yang diterima
String receivedString = "";
bool stringComplete = false;

// Nilai PWM saat ini
int leftRightPWM = 128;  // Nilai tengah
int forwardBackwardPWM = 128; // Nilai tengah

// Nilai PWM motor
int leftMotorPWM = 0;
int rightMotorPWM = 0;

// Ambang batas deadzone
const int DEADZONE = 10;

// Waktu terakhir data diterima
unsigned long lastDataTime = 0;
const unsigned long DATA_TIMEOUT = 1000; // 1 detik timeout

void setup() {
  Serial.begin(115200);
  
  // Inisialisasi Bluetooth
  SerialBT.begin("ESP32_Joystick"); // Nama perangkat Bluetooth
  Serial.println("Bluetooth dimulai, siap menerima koneksi");

  // Konfigurasi pin motor sebagai output
  pinMode(MOTOR_LEFT_PIN1, OUTPUT);
  pinMode(MOTOR_LEFT_PIN2, OUTPUT);
  pinMode(MOTOR_RIGHT_PIN1, OUTPUT);
  pinMode(MOTOR_RIGHT_PIN2, OUTPUT);

  // Konfigurasi PWM
  ledcSetup(PWM_CHANNEL_LEFT1, PWM_FREQ, PWM_RESOLUTION);
  ledcSetup(PWM_CHANNEL_LEFT2, PWM_FREQ, PWM_RESOLUTION);
  ledcSetup(PWM_CHANNEL_RIGHT1, PWM_FREQ, PWM_RESOLUTION);
  ledcSetup(PWM_CHANNEL_RIGHT2, PWM_FREQ, PWM_RESOLUTION);

  // Attach channel ke pin
  ledcAttachPin(MOTOR_LEFT_PIN1, PWM_CHANNEL_LEFT1);
  ledcAttachPin(MOTOR_LEFT_PIN2, PWM_CHANNEL_LEFT2);
  ledcAttachPin(MOTOR_RIGHT_PIN1, PWM_CHANNEL_RIGHT1);
  ledcAttachPin(MOTOR_RIGHT_PIN2, PWM_CHANNEL_RIGHT2);

  // Matikan semua motor di awal
  stopMotors();
}

void loop() {
  // Terima data dari aplikasi Flutter
  if (SerialBT.available()) {
    char inChar = (char)SerialBT.read();
    
    // Tambahkan ke string sampai newline
    if (inChar != '\n') {
      receivedString += inChar;
    } else {
      stringComplete = true;
    }

    // Perbarui waktu terakhir data diterima
    lastDataTime = millis();
  }
  
  // Proses data yang diterima
  if (stringComplete) {
    processJoystickData(receivedString);
    
    // Reset string
    receivedString = "";
    stringComplete = false;
  }

  // Hentikan motor jika tidak ada data dalam waktu tertentu
  if (millis() - lastDataTime > DATA_TIMEOUT) {
    stopMotors();
  }
  
  // Delay kecil
  delay(5);
}

// Fungsi untuk memproses data joystick
void processJoystickData(String data) {
  // Format data: "LR:xxx,FB:xxx"
  int lrIndex = data.indexOf("LR:");
  int fbIndex = data.indexOf("FB:");
  int commaIndex = data.indexOf(",");

  if (lrIndex != -1 && fbIndex != -1 && commaIndex != -1) {
    // Ekstrak nilai LR (Left-Right)
    String lrStr = data.substring(lrIndex + 3, commaIndex);
    // Ekstrak nilai FB (Forward-Backward)
    String fbStr = data.substring(fbIndex + 3);

    // Konversi ke integer
    int newLR = lrStr.toInt();
    int newFB = fbStr.toInt();

    // Update nilai PWM
    leftRightPWM = newLR;
    forwardBackwardPWM = newFB;

    // Debug output
    Serial.print("LR: ");
    Serial.print(leftRightPWM);
    Serial.print(", FB: ");
    Serial.println(forwardBackwardPWM);

    // Hitung nilai PWM motor berdasarkan joystick
    calculateMotorPWM();

    // Terapkan nilai PWM ke motor
    driveMotors();
  }
}

// Hitung nilai PWM motor berdasarkan nilai joystick
void calculateMotorPWM() {
  
  // Konversi rentang PWM (0-255) ke (-255 ke 255)
  int lrValue = map(forwardBackwardPWM, 0, 255, -255, 255);
  int fbValue = map(leftRightPWM, 0, 255, -255, 255);

  // Terapkan deadzone untuk mencegah drift
  if (abs(lrValue) < DEADZONE) lrValue = 0;
  if (abs(fbValue) < DEADZONE) fbValue = 0;

  // Algoritma differential drive
  // Menggabungkan maju/mundur dengan belok kiri/kanan
  leftMotorPWM = fbValue - lrValue;
  rightMotorPWM = fbValue + lrValue;

  // Batasi nilai PWM (-255 to 255)
  leftMotorPWM = constrain(leftMotorPWM, -255, 255);
  rightMotorPWM = constrain(rightMotorPWM, -255, 255);
}

// Terapkan nilai PWM ke motor
// Terapkan nilai PWM ke motor
void driveMotors() {
  // Status gerakan
  String movement = "";
  
  // Tentukan gerakan maju/mundur berdasarkan rata-rata PWM
  int avgPWM = (leftMotorPWM + rightMotorPWM) / 2;
  if (avgPWM > 0) {
    movement += "MAJU";
  } else if (avgPWM < 0) {
    movement += "MUNDUR";
  }
  
  // Tentukan gerakan kiri/kanan berdasarkan perbedaan PWM
  int diffPWM = rightMotorPWM - leftMotorPWM;
  if (diffPWM > 20) {  // Berikan threshold untuk menghindari deteksi yang terlalu sensitif
    if (!movement.isEmpty()) movement += " + ";
    movement += "KANAN";
  } else if (diffPWM < -20) {
    if (!movement.isEmpty()) movement += " + ";
    movement += "KIRI";
  }
  
  // Jika tidak ada gerakan
  if (movement.isEmpty()) {
    movement = "BERHENTI";
  }
  
  // Tampilkan status gerakan dan nilai PWM
  Serial.print(movement);
  Serial.print(" (L:");
  Serial.print(leftMotorPWM);
  Serial.print(", R:");
  Serial.print(rightMotorPWM);
  Serial.println(")");
  
  // Motor kiri
  if (leftMotorPWM > 0) {
    ledcWrite(PWM_CHANNEL_LEFT1, leftMotorPWM);
    ledcWrite(PWM_CHANNEL_LEFT2, 0);
  } else if (leftMotorPWM < 0) {
    ledcWrite(PWM_CHANNEL_LEFT1, 0);
    ledcWrite(PWM_CHANNEL_LEFT2, -leftMotorPWM);
  } else {
    // Berhenti
    ledcWrite(PWM_CHANNEL_LEFT1, 0);
    ledcWrite(PWM_CHANNEL_LEFT2, 0);
  }

  // Motor kanan
  if (rightMotorPWM > 0) {
    ledcWrite(PWM_CHANNEL_RIGHT1, rightMotorPWM);
    ledcWrite(PWM_CHANNEL_RIGHT2, 0);
  } else if (rightMotorPWM < 0) {
    ledcWrite(PWM_CHANNEL_RIGHT1, 0);
    ledcWrite(PWM_CHANNEL_RIGHT2, -rightMotorPWM);
  } else {
    // Berhenti
    ledcWrite(PWM_CHANNEL_RIGHT1, 0);
    ledcWrite(PWM_CHANNEL_RIGHT2, 0);
  }
}

// Hentikan semua motor
void stopMotors() {
  ledcWrite(PWM_CHANNEL_LEFT1, 0);
  ledcWrite(PWM_CHANNEL_LEFT2, 0);
  ledcWrite(PWM_CHANNEL_RIGHT1, 0);
  ledcWrite(PWM_CHANNEL_RIGHT2, 0);
}
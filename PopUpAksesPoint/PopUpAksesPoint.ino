
#ifdef ESP32
#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <SPIFFS.h>
#else
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#endif

// Konfigurasi WiFi Access Point
const char* ssid = "Akses Point";
const char* password = ""; // Minimal 8 karakter

// Konfigurasi DNS Server
const byte DNS_PORT = 53;
DNSServer dnsServer;

#ifdef ESP32
WebServer server(80);
#else
ESP8266WebServer server(80);
#endif

// IP untuk captive portal
IPAddress apIP(192, 168, 4, 1);
IPAddress netMsk(255, 255, 255, 0);

// Variabel untuk menyimpan data login
String savedUsername = "";
String savedPassword = "";
bool isLoggedIn = false;

// HTML untuk halaman login
const char* loginPage = R"(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>WiFi Login</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            margin: 0;
            padding: 0;
            display: flex;
            justify-content: center;
            align-items: center;
            min-height: 100vh;
        }
        .login-container {
            background: white;
            padding: 30px;
            border-radius: 10px;
            box-shadow: 0 10px 30px rgba(0,0,0,0.3);
            width: 100%;
            max-width: 400px;
        }
        .logo {
            text-align: center;
            margin-bottom: 30px;
        }
        .logo h1 {
            color: #333;
            margin: 0;
            font-size: 24px;
        }
        .form-group {
            margin-bottom: 20px;
        }
        label {
            display: block;
            margin-bottom: 5px;
            color: #555;
            font-weight: bold;
        }
        input[type="text"], input[type="password"] {
            width: 100%;
            padding: 12px;
            border: 2px solid #ddd;
            border-radius: 5px;
            font-size: 16px;
            box-sizing: border-box;
        }
        input[type="text"]:focus, input[type="password"]:focus {
            outline: none;
            border-color: #667eea;
        }
        .btn {
            width: 100%;
            padding: 12px;
            background: #667eea;
            color: white;
            border: none;
            border-radius: 5px;
            font-size: 16px;
            cursor: pointer;
            transition: background 0.3s;
        }
        .btn:hover {
            background: #5a67d8;
        }
        .info {
            text-align: center;
            margin-top: 20px;
            color: #666;
            font-size: 14px;
        }
        .status {
            padding: 10px;
            margin: 10px 0;
            border-radius: 5px;
            text-align: center;
        }
        .success {
            background: #d4edda;
            color: #155724;
            border: 1px solid #c3e6cb;
        }
        .error {
            background: #f8d7da;
            color: #721c24;
            border: 1px solid #f5c6cb;
        }
    </style>
</head>
<body>
    <div class="login-container">
        <div class="logo">
            <h1>🔒 WiFi Access</h1>
        </div>
        <form method="POST" action="/login">
            <div class="form-group">
                <label for="username">Username:</label>
                <input type="text" id="username" name="username" required>
            </div>
            <div class="form-group">
                <label for="password">Password:</label>
                <input type="password" id="password" name="password" required>
            </div>
            <button type="submit" class="btn">Login</button>
        </form>
        <div class="info">
            <p>Silakan masukkan username dan password untuk mengakses internet</p>
        </div>
    </div>
</body>
</html>
)";

// HTML untuk halaman sukses
const char* successPage = R"(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Login Berhasil</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            margin: 0;
            padding: 0;
            display: flex;
            justify-content: center;
            align-items: center;
            min-height: 100vh;
        }
        .success-container {
            background: white;
            padding: 40px;
            border-radius: 10px;
            box-shadow: 0 10px 30px rgba(0,0,0,0.3);
            text-align: center;
            max-width: 400px;
        }
        .success-icon {
            font-size: 48px;
            color: #28a745;
            margin-bottom: 20px;
        }
        h1 {
            color: #333;
            margin-bottom: 15px;
        }
        p {
            color: #666;
            margin-bottom: 20px;
        }
        .btn {
            padding: 12px 30px;
            background: #28a745;
            color: white;
            border: none;
            border-radius: 5px;
            font-size: 16px;
            cursor: pointer;
            text-decoration: none;
            display: inline-block;
        }
        .btn:hover {
            background: #218838;
        }
    </style>
</head>
<body>
    <div class="success-container">
        <div class="success-icon">✅</div>
        <h1>Login Berhasil!</h1>
        <p>Anda telah berhasil terhubung ke internet.</p>
        <a href="/dashboard" class="btn">Dashboard</a>
    </div>
</body>
</html>
)";

// HTML untuk dashboard
const char* dashboardPage = R"(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Dashboard</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background: #f5f5f5;
            margin: 0;
            padding: 20px;
        }
        .dashboard-container {
            max-width: 800px;
            margin: 0 auto;
            background: white;
            padding: 30px;
            border-radius: 10px;
            box-shadow: 0 5px 15px rgba(0,0,0,0.1);
        }
        .header {
            text-align: center;
            margin-bottom: 30px;
            padding-bottom: 20px;
            border-bottom: 2px solid #eee;
        }
        .info-card {
            background: #f8f9fa;
            padding: 20px;
            border-radius: 8px;
            margin-bottom: 20px;
            border-left: 4px solid #667eea;
        }
        .btn {
            padding: 10px 20px;
            background: #dc3545;
            color: white;
            border: none;
            border-radius: 5px;
            cursor: pointer;
            text-decoration: none;
            display: inline-block;
            margin-top: 10px;
        }
        .btn:hover {
            background: #c82333;
        }
    </style>
</head>
<body>
    <div class="dashboard-container">
        <div class="header">
            <h1>🌐 WiFi Dashboard</h1>
            <p>Selamat datang di sistem WiFi</p>
        </div>
        
        <div class="info-card">
            <h3>📊 Informasi Koneksi</h3>
            <p><strong>Status:</strong> Terhubung</p>
            <p><strong>SSID:</strong> ESP_CaptivePortal</p>
            <p><strong>IP Address:</strong> 192.168.4.1</p>
        </div>
        
        <div class="info-card">
            <h3>⚙️ Pengaturan</h3>
            <p>Anda dapat mengatur konfigurasi WiFi di sini</p>
            <a href="/logout" class="btn">Logout</a>
        </div>
    </div>
</body>
</html>
)";

void setup() {
    Serial.begin(115200);
    delay(1000);
    
    Serial.println("Starting ESP Captive Portal...");
    
    // Konfigurasi WiFi sebagai Access Point
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(apIP, apIP, netMsk);
    WiFi.softAP(ssid, password);
    
    Serial.println("Access Point Started");
    Serial.print("AP IP address: ");
    Serial.println(WiFi.softAPIP());
    
    // Konfigurasi DNS Server untuk captive portal
    dnsServer.start(DNS_PORT, "*", apIP);
    
    // Handler untuk root path
    server.on("/", handleRoot);
    server.on("/login", HTTP_POST, handleLogin);
    server.on("/success", handleSuccess);
    server.on("/dashboard", handleDashboard);
    server.on("/logout", handleLogout);
    
    // Handler untuk semua path yang tidak ditemukan (captive portal)
    server.onNotFound(handleNotFound);
    
    // Start web server
    server.begin();
    Serial.println("Web server started");
    Serial.println("Connect to WiFi: " + String(ssid));
    Serial.println("Password: " + String(password));
}

void loop() {
    dnsServer.processNextRequest();
    server.handleClient();
}

void handleRoot() {
    server.send(200, "text/html", loginPage);
}

void handleLogin() {
    String username = server.arg("username");
    String password = server.arg("password");
    
    Serial.println("Login attempt:");
    Serial.println("Username: " + username);
    Serial.println("Password: " + password);
    
    // Validasi login (bisa disesuaikan dengan kebutuhan)
    if (username.length() > 0 && password.length() > 0) {
        savedUsername = username;
        savedPassword = password;
        isLoggedIn = true;
        
        Serial.println("Login successful");
        server.sendHeader("Location", "/success");
        server.send(302, "text/plain", "");
    } else {
        Serial.println("Login failed");
        server.send(200, "text/html", loginPage);
    }
}

void handleSuccess() {
    if (isLoggedIn) {
        server.send(200, "text/html", successPage);
    } else {
        server.sendHeader("Location", "/");
        server.send(302, "text/plain", "");
    }
}

void handleDashboard() {
    if (isLoggedIn) {
        server.send(200, "text/html", dashboardPage);
    } else {
        server.sendHeader("Location", "/");
        server.send(302, "text/plain", "");
    }
}

void handleLogout() {
    isLoggedIn = false;
    savedUsername = "";
    savedPassword = "";
    
    Serial.println("User logged out");
    server.sendHeader("Location", "/");
    server.send(302, "text/plain", "");
}

void handleNotFound() {
    // Redirect semua request yang tidak ditemukan ke halaman login
    // Ini penting untuk captive portal
    server.sendHeader("Location", "/");
    server.send(302, "text/plain", "");
}
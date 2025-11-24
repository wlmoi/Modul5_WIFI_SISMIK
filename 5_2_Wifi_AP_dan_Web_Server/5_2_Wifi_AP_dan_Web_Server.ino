/*
 * Nama : William Anthony
 * NIM  : 13223048
 * Modul: 5
 * Percobaan: 5.2 - Wifi AP & Web Server
 * * --- INSTRUKSI PENGAMBILAN DATA ---
 * A. DATA PING (File: Ping.csv)
 * 1. Upload kode, lihat Serial Monitor untuk IP Address (default: 192.168.4.1).
 * 2. Hubungkan Laptop ke WiFi: "13223048" (Pass: password123).
 * 3. Buka CMD Laptop, ketik: "ping 192.168.4.1 -n 10".
 * 4. Catat Min, Max, Average, dan Packet Loss ke Excel.
 * * B. DATA LED FORM (File: LED Form.csv)
 * 1. Buka Browser, akses "192.168.4.1".
 * 2. Klik tombol "LED ON" -> Catat URL di browser dan kondisi LED fisik (Nyala).
 * 3. Klik tombol "LED OFF" -> Catat URL di browser dan kondisi LED fisik (Mati).
 */

#include <WiFi.h>
#include <WebServer.h>

const int ledPin = 2; // Built-in LED
const char* ssid = "13223048"; 
const char* password = "password123";

WebServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  // Buat Access Point
  WiFi.softAP(ssid, password);
  Serial.print("AP Created. Connect to "); Serial.println(ssid);
  Serial.print("IP Address: "); Serial.println(WiFi.softAPIP());

  // Halaman Utama
  server.on("/", []() {
    String html = "<h1>Halo, Saya William Anthony</h1>";
    html += "<h2>NIM: 13223048</h2>";
    html += "<p>Kontrol LED:</p>";
    html += "<p><a href=\"/on\"><button>LED ON</button></a></p>";
    html += "<p><a href=\"/off\"><button>LED OFF</button></a></p>";
    server.send(200, "text/html", html);
  });

  // Halaman ON
  server.on("/on", []() {
    digitalWrite(ledPin, HIGH);
    server.send(200, "text/html", "LED Hidup! <br><a href=\"/\">Kembali</a>");
    Serial.println("User akses /on -> LED Nyala");
  });

  // Halaman OFF
  server.on("/off", []() {
    digitalWrite(ledPin, LOW);
    server.send(200, "text/html", "LED Mati! <br><a href=\"/\">Kembali</a>");
    Serial.println("User akses /off -> LED Mati");
  });

  server.begin();
}

void loop() {
  server.handleClient();
}
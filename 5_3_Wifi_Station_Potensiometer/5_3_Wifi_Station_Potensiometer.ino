/*
 * Nama : William Anthony
 * NIM  : 13223048
 * Modul: 5
 * Percobaan: 5.3 - Wifi Station (Potensiometer)
 * * --- INSTRUKSI PENGAMBILAN DATA ---
 * 1. Ubah ssid/password di bawah sesuai WiFi Lab.
 * 2. Upload, buka Serial Monitor, catat IP Address yang didapat.
 * 3. Lakukan PING dari CMD Laptop ke IP tersebut (Isi Ping.csv).
 * 4. Buka Browser ke IP tersebut.
 * 5. Putar Potensiometer (Pin 34) ke posisi 0%, 25%, 50%, 100%.
 * 6. Bandingkan nilai Tegangan di Web dengan pengukuran manual/teori.
 * 7. Isi file "Potentiometer.csv".
 */

#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "NAMA_WIFI_LAB";      // GANTI INI
const char* password = "PASSWORD_WIFI";  // GANTI INI

const int potPin = 34; 
WebServer server(80);

void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("\nWiFi Connected.");
  Serial.print("Buka browser di: "); Serial.println(WiFi.localIP());

  server.on("/", []() {
    int val = analogRead(potPin);
    float voltage = val * (3.3 / 4095.0);
    
    String html = "<h1>Data Sensor William Anthony (13223048)</h1>";
    html += "<h3>Nilai ADC: " + String(val) + "</h3>";
    html += "<h3>Tegangan: " + String(voltage) + " V</h3>";
    html += "<script>setTimeout(function(){location.reload()}, 1000);</script>";
    
    server.send(200, "text/html", html);
  });

  server.begin();
}

void loop() {
  server.handleClient();
}
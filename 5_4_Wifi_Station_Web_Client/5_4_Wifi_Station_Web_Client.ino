/*
 * Nama : William Anthony
 * NIM  : 13223048
 * Modul: 5
 * Percobaan: 5.4 - Wifi Station & Web Client
 * * --- INSTRUKSI PENGAMBILAN DATA ---
 * 1. Pastikan Laptop menjalankan Server (bisa pakai Python script sederhana).
 * 2. Ganti 'serverName' dengan IP Laptop Anda.
 * 3. Tekan Tombol 1, 2, 3, atau 4 pada rangkaian.
 * 4. Amati Serial Monitor:
 * - Salin string JSON yang dikirim (misal: {"btn1":1...}) ke kolom "Nilai JSON Field".
 * - Salin "Response Code" (misal: 200) ke kolom "Kode Respons".
 * 5. Isi file "HTTP.csv".
 */

#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "NAMA_WIFI_LAB";       // GANTI INI
const char* password = "PASSWORD_WIFI";   // GANTI INI
String serverName = "http://192.168.1.100:5000/data"; // GANTI IP LAPTOP

const int btn1 = 18; // Sesuaikan Pin
const int btn2 = 19;
const int btn3 = 21;
const int btn4 = 22;

volatile bool sendFlag = false;

void IRAM_ATTR isr() {
  sendFlag = true;
}

void setup() {
  Serial.begin(115200);
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(btn3, INPUT_PULLUP);
  pinMode(btn4, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(btn1), isr, FALLING);
  attachInterrupt(digitalPinToInterrupt(btn2), isr, FALLING);
  attachInterrupt(digitalPinToInterrupt(btn3), isr, FALLING);
  attachInterrupt(digitalPinToInterrupt(btn4), isr, FALLING);

  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) delay(500);
  Serial.println("Siap kirim data...");
}

void loop() {
  if (sendFlag && WiFi.status() == WL_CONNECTED) {
    sendFlag = false; 
    delay(200); // Debounce sederhana

    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    // Membuat JSON Payload
    String json = "{";
    json += "\"btn1\":" + String(!digitalRead(btn1)) + ",";
    json += "\"btn2\":" + String(!digitalRead(btn2)) + ",";
    json += "\"btn3\":" + String(!digitalRead(btn3)) + ",";
    json += "\"btn4\":" + String(!digitalRead(btn4));
    json += "}";

    Serial.print("Mengirim JSON: "); Serial.println(json); // COPY INI KE EXCEL
    
    int httpResponseCode = http.POST(json);
    Serial.print("Kode Respons: "); Serial.println(httpResponseCode); // COPY INI KE EXCEL
    
    http.end();
  }
}
/*
 * Nama : William Anthony (13223048) - SERVER LATENSI
 * Percobaan 5.6
 * Instruksi:
 * 1. Hubungkan Pin 2 ke Probe Osiloskop CH2.
 * 2. Upload kode, cek Serial Monitor untuk tahu IP Address.
 * 3. Masukkan IP tersebut ke kode Client.
 * 4. Ukur selisih waktu (Delta T) antara CH1 (Client) dan CH2 (Server).
 * 5. Isi "Latensi.csv".
 */
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "NAMA_WIFI_LAB"; // GANTI INI
const char* password = "PASSWORD";    // GANTI INI

const int outPin = 2; 
WebServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(outPin, OUTPUT);
  digitalWrite(outPin, LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  Serial.print("IP Server: "); Serial.println(WiFi.localIP());

  server.on("/trigger", []() {
    digitalWrite(outPin, HIGH); // Sinyal Naik
    server.send(200, "text/plain", "OK");
    delay(50);
    digitalWrite(outPin, LOW);
  });
  server.begin();
}
void loop() { server.handleClient(); }
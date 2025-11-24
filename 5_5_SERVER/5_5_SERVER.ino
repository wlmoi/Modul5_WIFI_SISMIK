/*
 * Nama : William Anthony (13223048) - SERVER
 * Percobaan 5.5
 * Instruksi: Hubungkan LED ke Pin 18, 19, 21, 22.
 * Amati nyala LED saat sakelar di Client berubah.
 */
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ESP32_Server_William";
const char* password = "password123";
const int ledPins[4] = {18, 19, 21, 22}; 

WebServer server(80);

void setup() {
  Serial.begin(115200);
  for(int i=0; i<4; i++) { pinMode(ledPins[i], OUTPUT); digitalWrite(ledPins[i], LOW); }

  WiFi.softAP(ssid, password);
  Serial.println("Server Ready.");

  server.on("/update", []() {
    for (int i = 0; i < 4; i++) {
      String param = "s" + String(i + 1);
      if (server.hasArg(param)) {
        digitalWrite(ledPins[i], server.arg(param).toInt());
      }
    }
    server.send(200, "text/plain", "OK");
  });
  server.begin();
}
void loop() { server.handleClient(); }
/*
 * Nama : William Anthony (13223048) - CLIENT
 * Percobaan 5.5
 * Instruksi: Hubungkan DIP Switch ke Pin 18, 19, 21, 22.
 * 1. Ubah posisi sakelar.
 * 2. Isi file "LED Sakelar.csv":
 * - Input Sakelar: 1 (On) atau 0 (Off).
 * - Output LED: Lihat nyala LED di ESP32 SERVER.
 */
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "ESP32_Server_William";
const char* password = "password123";
String urlBase = "http://192.168.4.1/update";

const int swPins[4] = {18, 19, 21, 22};

void setup() {
  Serial.begin(115200);
  for(int i=0; i<4; i++) pinMode(swPins[i], INPUT_PULLUP);
  
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) delay(500);
  Serial.println("Terhubung ke Server.");
}

void loop() {
  if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;
    String url = urlBase + "?";
    for(int i=0; i<4; i++){
      // !digitalRead karena INPUT_PULLUP (Low = On)
      url += "s" + String(i+1) + "=" + String(!digitalRead(swPins[i])); 
      if(i<3) url += "&";
    }
    http.begin(url);
    http.GET();
    http.end();
  }
  delay(200); 
}
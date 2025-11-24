/*
 * Nama : William Anthony (13223048) - CLIENT LATENSI
 * Percobaan 5.6
 * Instruksi: 
 * 1. Hubungkan Pin 34 ke Generator Sinyal (Square Wave).
 * 2. Pasang Probe Osiloskop CH1 di Pin 34 ini.
 * 3. Ganti IP Server di bawah sesuai IP ESP32 Server.
 */
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "NAMA_WIFI_LAB"; // GANTI INI
const char* password = "PASSWORD";    // GANTI INI
String serverURL = "http://192.168.X.X/trigger"; // GANTI IP SERVER

const int inputPin = 34; 
bool lastState = LOW;

void setup() {
  pinMode(inputPin, INPUT);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) delay(500);
}

void loop() {
  bool currentState = digitalRead(inputPin);
  // Deteksi Rising Edge
  if (currentState == HIGH && lastState == LOW) {
    if(WiFi.status() == WL_CONNECTED){
      HTTPClient http;
      http.begin(serverURL);
      http.GET(); 
      http.end();
    }
  }
  lastState = currentState;
}
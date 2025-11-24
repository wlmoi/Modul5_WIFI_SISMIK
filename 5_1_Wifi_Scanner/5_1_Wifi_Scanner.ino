/*
 * Nama : William Anthony
 * NIM  : 13223048
 * Modul: 5
 * Percobaan: 5.1 - Wifi Scanner
 * * --- INSTRUKSI PENGAMBILAN DATA ---
 * 1. Upload kode ini ke ESP32.
 * 2. Buka Serial Monitor (Baudrate 115200).
 * 3. Amati daftar WiFi yang muncul.
 * 4. Buka file Excel "Wifi Scanner.csv".
 * 5. Isi kolom: SSID, RSSI (dBm), Channel, dan Tipe Enkripsi sesuai output di Serial Monitor.
 */

#include "WiFi.h"

void setup() {
  Serial.begin(115200);
  
  // Set WiFi ke mode Station dan disconnect dari jaringan sebelumnya
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  
  Serial.println("Setup selesai. William Anthony (13223048) siap scan WiFi...");
}

void loop() {
  Serial.println("Memulai pemindaian WiFi...");

  // Scan jaringan (sinkron)
  int n = WiFi.scanNetworks();
  
  if (n == 0) {
    Serial.println("Tidak ada jaringan ditemukan.");
  } else {
    Serial.print(n);
    Serial.println(" jaringan ditemukan:");
    
    // Header Tabel Serial
    Serial.println("No | SSID | RSSI | Channel | Encrypt"); 
    
    for (int i = 0; i < n; ++i) {
      // Cetak data untuk diisi ke Excel
      Serial.print(i + 1);
      Serial.print(" | ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" | ");
      Serial.print(WiFi.RSSI(i));
      Serial.print(" dBm | ");
      Serial.print(WiFi.channel(i)); // Data untuk kolom Channel
      Serial.print(" | ");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?"Open":"Secured");
      delay(10);
    }
  }
  Serial.println("");

  // Tunggu 5 detik sebelum scan ulang agar mudah mencatat
  delay(5000);
}
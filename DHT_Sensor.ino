#include "DHT.h"
#include <WiFi.h>
#include <HTTPClient.h>

#define DHTPIN 13   
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);


// Sesuaikan ssid dengan nama wifi dan password wifi tersebut
const char* ssid = "Infinix NOTE 30 Pro";
const char* password = "abcabcabc";


// Sesuaikan server dengan IPv4 Adress
const char* serverName = "http://192.168.82.125:5000/sensor/data";

void setup() {
  Serial.begin(115200);
  Serial.println(F("DHTxx test!"));

  dht.begin();

  // Mengkoneksi wifi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  delay(2000);

  // Membaca kelembaban dan suhu menggunakan sensor DHT
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));

  HTTPClient http;

  String url = String(serverName) + "?temperature=" + String(t) + "&kelembapan=" + String(h);

  // Mengirim url menggunakan parameter, suhu dan kelembapan yang sudah dibaca
  http.begin(url);

  // Mendapatkan response code dengan POST yang ada pada kode python
  int httpResponseCode = http.POST("");

  // Jika code 200 maka berhasil
  if (httpResponseCode == 200) {
    // Mengambil yang direturn pada kode di python pada kode yang saya buat adalah "Berhasil disimpan ke server"
    String response = http.getString();
    Serial.println(httpResponseCode);
    Serial.println(response);
  }
  else {
    Serial.print("Error on sending POST: ");
    // Menampilkan error code jika terjadi error
    Serial.println(httpResponseCode);
  }
}

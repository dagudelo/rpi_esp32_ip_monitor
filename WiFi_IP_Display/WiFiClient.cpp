#include "WiFiClient.h"
#include <ArduinoJson.h>

void IPFetcherClient::connectWiFi(const char* ssid, const char* password) {
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("ESP32 IP address: ");
  Serial.println(WiFi.localIP());
}

RPiData IPFetcherClient::getRPiData(const char* host, int port) {
  HTTPClient http;
  RPiData data; // Create an instance of the struct
  data.error = ""; // Initialize error string

  String url = "http://" + String(host) + ":" + String(port) + "/ip";

  Serial.print("Fetching RPi data from: ");
  Serial.println(url);

  http.begin(url);
  int httpCode = http.GET();

  if (httpCode > 0) { // Check for the returning code
    String responseString = http.getString();
    Serial.print("Received JSON: ");
    Serial.println(responseString);

    StaticJsonDocument<500> doc; // Increased size for more data
    DeserializationError error = deserializeJson(doc, responseString);

    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      data.error = "Error parsing JSON";
      return data;
    }

    // Parse fields
    data.ipAddress = doc["ip_address"].as<String>();
    data.hostname = doc["hostname"].as<String>();
    data.cpuLoadPercent = doc["cpu_load_percent"].as<float>();
    data.memTotalMB = doc["memory_load"]["total_mb"].as<float>();
    data.memUsedMB = doc["memory_load"]["used_mb"].as<float>();
    data.memPercent = doc["memory_load"]["percent"].as<float>();
    data.coreTempCelsius = doc["core_temperature_celsius"].as<float>();

  } else {
    Serial.printf("HTTP GET failed, error: %s\n", http.errorToString(httpCode).c_str());
    data.error = "HTTP Error";
  }
  http.end();
  return data;
}
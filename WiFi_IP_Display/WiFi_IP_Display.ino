#include "WiFiDisplay.h"
#include "WiFiClient.h"

// Replace with your Wi-Fi credentials
const char* ssid = "Agudelo Bonilla Mesh";
const char* password = "V1CT0R1446U5T1N";

// Array of Raspberry Pi IP addresses
// IMPORTANT: Replace these with the actual IP addresses of your Raspberry Pis
const char* raspberryPiIPs[] = {
  "192.168.10.36",
  "192.168.10.39",
  "192.168.10.20",
  "192.168.10.18",
  "192.168.10.43",
  "192.168.10.23"
 // Add more as needed
};
const int numRaspberryPis = sizeof(raspberryPiIPs) / sizeof(raspberryPiIPs[0]);

const int raspberryPiPort = 6000;

WiFiDisplay display;
IPFetcherClient ipClient;

void setup() {
  Serial.begin(115200);
  display.init();
  ipClient.connectWiFi(ssid, password);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    for (int i = 0; i < numRaspberryPis; i++) {
      RPiData data = ipClient.getRPiData(raspberryPiIPs[i], raspberryPiPort);
      display.clearScreen();
      
      if (data.error.length() > 0) {
        display.displayText("Error: ", 0, 0);
        display.displayText(data.error, 0, 20);
      } else {
        display.displayText("Host: " + data.hostname, 0, 0);
        display.displayText("IP: " + data.ipAddress, 0, 20);
        display.displayText("CPU: " + String(data.cpuLoadPercent) + "%", 0, 40);
        display.displayText("Mem: " + String(data.memPercent) + "%", 0, 60);
        display.displayText("Temp: " + String(data.coreTempCelsius) + "C", 0, 80);
      }
      delay(5000); // Display each RPi's data for 5 seconds
    }
  } else {
    display.clearScreen();
    display.displayText("WiFi Disconnected", 0, 0);
    ipClient.connectWiFi(ssid, password); // Try to reconnect
  }
  delay(1000); // Short delay before re-checking WiFi status
}
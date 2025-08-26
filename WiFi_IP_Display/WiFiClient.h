#ifndef WIFI_CLIENT_H
#define WIFI_CLIENT_H

#include <WiFi.h>
#include <HTTPClient.h>

// New struct to hold parsed data
struct RPiData {
  String ipAddress;
  String hostname;
  float cpuLoadPercent;
  float memTotalMB;
  float memUsedMB;
  float memPercent;
  float coreTempCelsius;
  String error; // To store parsing or HTTP errors
};

class IPFetcherClient {
public:
  void connectWiFi(const char* ssid, const char* password);
  RPiData getRPiData(const char* host, int port);
};

#endif
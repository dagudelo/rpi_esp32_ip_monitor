#ifndef WIFI_DISPLAY_H
#define WIFI_DISPLAY_H

#include <TFT_eSPI.h>

class WiFiDisplay {
public:
  void init();
  void clearScreen();
  void displayText(const String& text, int x, int y);

private:
  TFT_eSPI tft;
};

#endif
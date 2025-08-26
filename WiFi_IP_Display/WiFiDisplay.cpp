#include "WiFiDisplay.h"
#include <SPI.h>
#include <Wire.h>

// Include the correct setup file for your board
#include <User_Setup_Select.h>

void WiFiDisplay::init() {
  tft.init();
  tft.setRotation(1); // Adjust rotation as needed
  tft.fillScreen(TFT_BLACK);
  tft.setTextFont(2);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
}

void WiFiDisplay::clearScreen() {
  tft.fillScreen(TFT_BLACK);
}

void WiFiDisplay::displayText(const String& text, int x, int y) {
  tft.drawString(text, x, y);
}
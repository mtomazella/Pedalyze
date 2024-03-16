#pragma once

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class Display : public Adafruit_SSD1306
{
public:
  Display(int width, int height, TwoWire *wire, int reset) : Adafruit_SSD1306(width, height, wire, reset) {}

  void init(int address)
  {
    if (!this->begin(SSD1306_SWITCHCAPVCC, address))
    {
      Serial.println(F("SSD1306 allocation failed"));
      while (true)
        ;
    }
    this->clearDisplay();
  }
};
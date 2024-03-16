#pragma once

#include "Display.h"
#include "State.h"

class Tab
{
public:
  virtual void setup(State *state, Display *display);

  bool shouldDraw(State *state)
  {
    static unsigned long lastDraw = 0;
    long time = millis();
    if (time - lastDraw < 200)
      return false;
    lastDraw = time;
    return true;
  }

  virtual void draw(State *state, Display *display);
};

class TestTab : public Tab
{
public:
  void setup(State *state, Display *display) {}

  void draw(State *state, Display *display)
  {
    display->setTextSize(2);
    display->fillScreen(BLACK);
    display->setTextColor(WHITE);
    display->setCursor(0, 28);
    display->println(millis());
    display->display();
  }
};

// display->setTextSize(1);
// display->setTextColor(WHITE);
// display->setCursor(0, 28);
// display->println("Hello world!");
// display->display();
// delay(2000);
// display->clearDisplay();

// // Display Inverted Text
// display->setTextColor(BLACK, WHITE); // 'inverted' text
// display->setCursor(0, 28);
// display->println("Hello world!");
// display->display();
// delay(2000);
// display->clearDisplay();

// // Changing Font Size
// display->setTextColor(WHITE);
// display->setCursor(0, 24);
// display->setTextSize(2);
// display->println("Hello!");
// display->display();
// delay(2000);
// display->clearDisplay();

// // Display Numbers
// display->setTextSize(1);
// display->setCursor(0, 28);
// display->println(123456789);
// display->display();
// delay(2000);
// display->clearDisplay();

// // Specifying Base For Numbers
// display->setCursor(0, 28);
// display->print("0x");
// display->print(0xFF, HEX);
// display->print("(HEX) = ");
// display->print(0xFF, DEC);
// display->println("(DEC)");
// display->display();
// delay(2000);
// display->clearDisplay();

// // Display ASCII Characters
// display->setCursor(0, 24);
// display->setTextSize(2);
// display->write(3);
// display->display();
// delay(2000);
// display->clearDisplay();

// // Scroll full screen
// display->setCursor(0, 0);
// display->setTextSize(1);
// display->println("Full");
// display->println("screen");
// display->println("scrolling!");
// display->display();
// display->startscrollright(0x00, 0x07);
// delay(2000);
// display->stopscroll();
// delay(1000);
// display->startscrollleft(0x00, 0x07);
// delay(2000);
// display->stopscroll();
// delay(1000);
// display->startscrolldiagright(0x00, 0x07);
// delay(2000);
// display->startscrolldiagleft(0x00, 0x07);
// delay(2000);
// display->stopscroll();
// display->clearDisplay();

// // Scroll part of the screen
// display->setCursor(0, 0);
// display->setTextSize(1);
// display->println("Scroll");
// display->println("some part");
// display->println("of the screen.");
// display->display();
// display->startscrollright(0x00, 0x00);
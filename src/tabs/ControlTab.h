#pragma once

#include "config.h"
#include "Tab.h"
#include "State.h"

class ControlTab : public Tab
{
public:
  void setup(State *state) {}

  void processInput(State *state, Input *input)
  {
  }

  void draw(State *state, Display *display)
  {
    display->clearDisplay();
    display->fillScreen(BLACK);
    display->setTextSize(2);
    display->setTextColor(WHITE);
    display->setCursor(0, SCREEN_HEIGHT / 2 - 10);
    display->print("Control Tab");
    display->display();
  }
};

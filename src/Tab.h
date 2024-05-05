#pragma once

#include "config.h"
#include "Display.h"
#include "State.h"
#include "Input.h"

class Tab
{
public:
  virtual void setup(State *state);

  virtual void processInput(State *state, Input *input);

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

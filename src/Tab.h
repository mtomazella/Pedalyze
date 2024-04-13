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

class TestTab : public Tab
{
public:
  void setup(State *state) {}

  void processInput(State *state, Input *input)
  {
    InputEvent event = input->process();

    static bool processEncoder = true;
    if (event.encoderDelta != 0)
    {
      if (processEncoder) // Why? Don't ask
      {
        state->T_xOffset += event.encoderDelta;
        processEncoder = false;
      }
      else
        processEncoder = true;
    }

    state->menuSwitchPosition = event.menuSwitchPosition;
    state->menuSwitchReading = event.menuSwitchReading;
  }

  void draw(State *state, Display *display)
  {
    // display->setTextSize(2);
    // display->fillScreen(BLACK);
    // display->setTextColor(WHITE);
    // display->setCursor(0, 28);
    // display->println(millis());
    // display->display();

    // circle at the center of the screen
    display->clearDisplay();
    display->fillScreen(WHITE);
    display->setTextSize(1);
    display->setTextColor(BLACK);
    display->setCursor(0, 0);
    display->print(state->T_xOffset);
    display->print(' ');
    display->print(state->menuSwitchPosition);
    display->print(' ');
    display->print(state->menuSwitchReading);
    display->fillCircle(SCREEN_WIDTH / 2 + state->T_xOffset, SCREEN_HEIGHT / 2, 10, BLACK);
    display->display();
  }
};

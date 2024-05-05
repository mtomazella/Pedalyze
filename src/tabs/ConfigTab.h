#pragma once

#include "config.h"
#include "Tab.h"
#include "State.h"

#define menuSize1 2

class ConfigTab : public Tab
{
private:
  char *menuItems[menuSize1] = {ENCODER_TEST_TAB_NAME, MIDI_TEST_TAB_NAME};

public:
  void setup(State *state) {}

  void processInput(State *state, Input *input)
  {
    InputEvent event = input->process();

    state->Cf_menuPosition1 += event.encoderDelta;
    if (state->Cf_menuPosition1 < 0)
    {
      state->Cf_menuPosition1 = 0;
    }
    else if (state->Cf_menuPosition1 > menuSize1 - 1)
    {
      state->Cf_menuPosition1 = menuSize1 - 1;
    }

    if (event.encoderButton.clicks > 0)
    {
      state->tabId = 3 + state->Cf_menuPosition1;
      return;
    }
  }

  void draw(State *state, Display *display)
  {
    display->clearDisplay();
    display->fillScreen(BLACK);
    display->setTextColor(WHITE);
    display->setTextSize(1);
    display->setCursor(0, 0);
    display->print(CONFIG_TAB_NAME);
    display->setTextSize(2);
    display->setCursor(0, SCREEN_HEIGHT / 2 - 10);
    display->print(menuItems[state->Cf_menuPosition1]);
    display->display();
  }
};

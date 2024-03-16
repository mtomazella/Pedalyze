#pragma once

#include "config.h"
#include "Tab.h"
#include "State.h"

class Menu
{
private:
  State *state;
  Tab *tabs[MAX_TABS];

public:
  void init(State *state, Tab **tabs, int tabCount)
  {
    this->state = state;

    for (int i = 0; i < tabCount; i++)
    {
      this->tabs[i] = tabs[i];
    }
  }

  Tab *getCurrentTab()
  {
    return this->tabs[state->tabId];
  }
};
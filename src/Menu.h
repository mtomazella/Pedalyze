#pragma once

#include "config.h"
#include "Tab.h"
#include "State.h"

class Menu
{
private:
  State *state;
  Tab *tabs[MAX_TABS];
  int lastTabSeen = -1;

public:
  void init(State *state, Tab **tabs, int tabCount)
  {
    this->state = state;

    for (int i = 0; i < tabCount; i++)
    {
      this->tabs[i] = tabs[i];
    }
  }

  void loop()
  {
    if (state->tabId != lastTabSeen)
    {
      lastTabSeen = state->tabId;
      getCurrentTab()->setup(state);
    }
  }

  Tab *getCurrentTab()
  {
    return this->tabs[state->tabId];
  }
};
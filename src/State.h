#pragma once

#include "config.h"

class State
{
public:
  int tabId = INITIAL_TAB;

  // Config tab
  int Cf_menuPosition1 = 0;

  // Test tab
  int T_xOffset = 0;
  int menuSwitchPosition = 0;
  int menuSwitchReading = 0;
};
#pragma once

#include "config.h"

class State
{
public:
  int tabId = INITIAL_TAB;

  // Config tab
  int Cf_menuPosition1 = 0;

  // Encoder Test tab
  int ETT_xOffset = 0;
  int ETT_clicks = 0;
  int ETT_doubleClicks = 0;
  int ETT_holdClicks = 0;
  bool ETT_holding = false;
  long ETT_lastPress = 0;
  long ETT_lastRelease = 0;
};
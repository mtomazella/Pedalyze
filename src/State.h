#pragma once

#include "config.h"
#include "ButtonEvent.h"

class State
{
public:
  int tabId = INITIAL_TAB;
  int previousTabId = INITIAL_TAB;

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

  // Midi Test tab
  int Mtt_midiNote = 60;
  int Mtt_previousNote = 60;
  bool Mtt_sending = false;

  // Matrix Test tab
  bool Mxt_buttonsHolding[MATRIX_LENGTH];

  void changeTab(int tabId)
  {
    previousTabId = this->tabId;
    this->tabId = tabId;
  }
};
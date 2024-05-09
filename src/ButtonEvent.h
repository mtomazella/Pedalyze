#pragma once

class ButtonEvent
{
public:
  unsigned long lastPress = 0;
  unsigned long lastRelease = 0;
  bool holding = false;
  int clicks = 0;
  int doubleClicks = 0; // TODO: not implemented yet
  int holdClicks = 0;

  ButtonEvent()
  {
    lastPress = 0;
    lastRelease = 0;
    holding = false;
    clicks = 0;
    doubleClicks = 0;
    holdClicks = 0;
  }

  void clean()
  {
    clicks = 0;
    doubleClicks = 0;
    holdClicks = 0;
  }

  ButtonEvent copy()
  {
    ButtonEvent copiedEvent;
    copiedEvent.lastPress = this->lastPress;
    copiedEvent.lastRelease = this->lastRelease;
    copiedEvent.holding = this->holding;
    copiedEvent.clicks = this->clicks;
    copiedEvent.doubleClicks = this->doubleClicks;
    copiedEvent.holdClicks = this->holdClicks;
    return copiedEvent;
  }
};
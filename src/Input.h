#pragma once

#include "Encoder.h"
#include "config.h"

class ButtonEvent
{
public:
  long lastPress = 0;
  long lastRelease = 0;
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

class InputEvent
{
public:
  long lastProcessed = 0;

  int encoderDelta = 0;
  ButtonEvent encoderButton = ButtonEvent();

  long matrixLastPresses[MATRIX_LENGTH];
  long matrixLastReleases[MATRIX_LENGTH];
  bool matrixHolding[MATRIX_LENGTH];
  int matrixClicks[MATRIX_LENGTH];
  int matrixDoubleClicks[MATRIX_LENGTH];

  int menuSwitchPosition = 0;
  bool menuSwitchPositionChanged = false;
  int menuSwitchReading = 0;

  InputEvent()
  {
    clean();

    for (int i = 0; i < MATRIX_LENGTH; i++)
      matrixLastPresses[i] = 0;
  }

  void clean()
  {
    encoderDelta = 0;
    encoderButton.clean();
    menuSwitchPositionChanged = false;
    menuSwitchReading = 0;

    for (int i = 0; i < MATRIX_LENGTH; i++)
    {
      matrixClicks[i] = 0;
      matrixDoubleClicks[i] = 0;
    }
  }

  InputEvent copy()
  {
    InputEvent copiedEvent;
    copiedEvent.lastProcessed = this->lastProcessed;
    copiedEvent.encoderDelta = this->encoderDelta;
    copiedEvent.encoderButton = this->encoderButton.copy();
    copiedEvent.menuSwitchPosition = this->menuSwitchPosition;
    copiedEvent.menuSwitchPositionChanged = this->menuSwitchPositionChanged;
    copiedEvent.menuSwitchReading = this->menuSwitchReading;

    for (int i = 0; i < MATRIX_LENGTH; i++)
    {
      copiedEvent.matrixLastPresses[i] = this->matrixLastPresses[i];
      copiedEvent.matrixClicks[i] = this->matrixClicks[i];
      copiedEvent.matrixDoubleClicks[i] = this->matrixDoubleClicks[i];
    }

    return copiedEvent;
  }
};

class Input
{
public:
  Encoder encoder = Encoder(ENCODER_DT, ENCODER_CLK);
  InputEvent event;

  void init()
  {
    pinMode(ENCODER_SW, INPUT);
  }

  InputEvent sense()
  {
    long time = millis();

    // This workaround is needed because the program is reading the half pulses of the encoder
    int reading = encoder.readAndReset();
    static bool processEncoder = true;
    if (reading != 0)
    {
      if (processEncoder)
      {
        event.encoderDelta += reading;
        processEncoder = false;
      }
      else
        processEncoder = true;
    }

    bool encoderButtonPressed = digitalRead(ENCODER_SW) == LOW;
    if (encoderButtonPressed)
    {
      event.encoderButton.holding = true;
      if (event.encoderButton.lastRelease >= event.encoderButton.lastPress)
      {
        event.encoderButton.lastPress = time;
      }
    }
    else
    {
      event.encoderButton.holding = false;
      if (event.encoderButton.lastPress > event.encoderButton.lastRelease)
      {
        int currentPressTime = event.encoderButton.lastPress;
        int previousPressReleaseTime = event.encoderButton.lastRelease;
        event.encoderButton.lastRelease = time;

        if (currentPressTime - previousPressReleaseTime < DEBOUNCE_INTERVAL)
        {
        }
        else if (time - currentPressTime > HOLD_CLICK_INTERVAL)
        {
          event.encoderButton.holdClicks++;
        }
        else
        {
          event.encoderButton.clicks++;
        }
      }
    }

    int menuSwitchReading = analogRead(MENU_SWITCH);
    int readingLimit1 = 1024 / 3;
    int readingLimit2 = 1024 / 3 * 2;
    int newMenuSwitchPosition = 1;
    if (menuSwitchReading < readingLimit1)
      newMenuSwitchPosition = 0;
    else if (menuSwitchReading < readingLimit2)
      newMenuSwitchPosition = 2;
    event.menuSwitchPositionChanged = event.menuSwitchPosition != newMenuSwitchPosition;
    event.menuSwitchPosition = newMenuSwitchPosition;
    event.menuSwitchReading = menuSwitchReading;

    return event.copy();
  }

  InputEvent process()
  {
    InputEvent newEvent = event.copy();
    event.clean();
    event.lastProcessed = millis();
    return newEvent;
  }
};
#pragma once

#include "Encoder.h"
#include "config.h"

class InputEvent
{
public:
  long lastProcessed = 0;
  int encoderDelta = 0;
  long encoderButtonLastPress = 0;
  int encoderButtonClicks = 0;
  int encoderButtonDoubleClicks = 0;
  long matrixLastPresses[MATRIX_LENGTH];
  int matrixClicks[MATRIX_LENGTH];
  int matrixDoubleClicks[MATRIX_LENGTH];
  int menuSwitchPosition = 0;
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
    encoderButtonClicks = 0;
    encoderButtonDoubleClicks = 0;
    menuSwitchPosition = 0;
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
    copiedEvent.encoderButtonLastPress = this->encoderButtonLastPress;
    copiedEvent.encoderButtonClicks = this->encoderButtonClicks;
    copiedEvent.encoderButtonDoubleClicks = this->encoderButtonDoubleClicks;
    copiedEvent.menuSwitchPosition = this->menuSwitchPosition;
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

  void sense()
  {
    event.encoderDelta += encoder.readAndReset();

    int menuSwitchReading = analogRead(MENU_SWITCH);
    int readingLimit1 = 1024 / 3;
    int readingLimit2 = 1024 / 3 * 2;
    if (menuSwitchReading < readingLimit1)
      event.menuSwitchPosition = 0;
    else if (menuSwitchReading < readingLimit2)
      event.menuSwitchPosition = 2;
    else
      event.menuSwitchPosition = 1;
    event.menuSwitchReading = menuSwitchReading;
  }

  InputEvent process()
  {
    InputEvent newEvent = event.copy();
    event.clean();
    event.lastProcessed = millis();
    return newEvent;
  }
};
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
  }

  InputEvent process()
  {
    InputEvent newEvent = event.copy();
    event.clean();
    event.lastProcessed = millis();
    return newEvent;
  }
};
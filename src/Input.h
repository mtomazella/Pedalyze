#pragma once

#include "Encoder.h"
#include "config.h"
#include "ButtonEvent.h"
#include "Adafruit_MCP23X08.h"

class InputEvent
{
public:
  unsigned long lastProcessed = 0;

  int encoderDelta = 0;
  ButtonEvent encoderButton = ButtonEvent();

  bool matrixButtonsHolding[MATRIX_LENGTH];

  int menuSwitchPosition = 0;
  bool menuSwitchPositionChanged = false;
  int menuSwitchReading = 0;

  InputEvent()
  {
    clean();
  }

  void clean()
  {
    encoderDelta = 0;
    encoderButton.clean();
    menuSwitchPositionChanged = false;
    menuSwitchReading = 0;

    for (int i = 0; i < MATRIX_LENGTH; i++)
    {
      matrixButtonsHolding[i] = false;
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
      copiedEvent.matrixButtonsHolding[i] = this->matrixButtonsHolding[i];
    }

    return copiedEvent;
  }
};

class Input
{
public:
  Encoder encoder = Encoder(ENCODER_DT, ENCODER_CLK);
  InputEvent event;
  Adafruit_MCP23X08 mcp = Adafruit_MCP23X08();

  void init()
  {
    pinMode(ENCODER_SW, INPUT);
    bool result = mcp.begin_I2C(0x20);

    Serial.print("MCP23008 begin result: ");
    Serial.println(result);

    for (int i = 0; i < MATRIX_LENGTH; i++)
    {
      mcp.pinMode(i, INPUT_PULLUP);
    }
  }

  InputEvent sense()
  {
    unsigned long time = millis();

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
        unsigned long currentPressTime = event.encoderButton.lastPress;
        unsigned long previousPressReleaseTime = event.encoderButton.lastRelease;
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

      for (int i = 0; i < 8; i++)
      {
        bool buttonPressed = mcp.digitalRead(i) == LOW;
        event.matrixButtonsHolding[i] = buttonPressed;
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
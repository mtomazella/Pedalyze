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

  int channelValues[MAX_CHANNELS];

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
    for (int i = 0; i < MAX_CHANNELS; i++)
    {
      channelValues[i] = 0;
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

    for (int i = 0; i < MAX_CHANNELS; i++)
    {
      copiedEvent.channelValues[i] = this->channelValues[i];
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
  int rows[MATRIX_HEIGHT] = {ROW1, ROW2, ROW3};
  int cols[MATRIX_WIDTH] = {COL1, COL2, COL3, COL4};
  // int channels[MAX_CHANNELS] = {CH1, CH2, CH3, CH4, CH5};
  int channels[MAX_CHANNELS] = {CH1, CH2};

  void init()
  {
    pinMode(ENCODER_SW, INPUT);
    bool result = mcp.begin_I2C(0x20);

    Serial.print("MCP23008 begin result: ");
    Serial.println(result);

    for (int i = 0; i < MATRIX_WIDTH; i++)
    {
      mcp.pinMode(cols[i], INPUT_PULLUP);
    }
    for (int i = 0; i < MATRIX_HEIGHT; i++)
    {
      mcp.pinMode(rows[i], OUTPUT);
    }
    for (int i = 0; i < MAX_CHANNELS; i++)
    {
      pinMode(channels[i], INPUT_PULLUP);
    }
  }

  InputEvent sense()
  {
    unsigned long time = millis();

    // --------- ENCODER READING
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
    // ---------

    // --------- ENCODER BUTTON READING
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
    }
    // ---------

    // --------- MATRIX READING
    for (int i = 0; i < MATRIX_HEIGHT; i++)
    {
      mcp.digitalWrite(rows[i], LOW);
      for (int j = 0; j < MATRIX_WIDTH; j++)
      {
        mcp.digitalWrite(cols[j], HIGH);
        bool buttonPressed = mcp.digitalRead(cols[j]) == LOW;
        event.matrixButtonsHolding[i * MATRIX_WIDTH + j] = buttonPressed;
      }
      mcp.digitalWrite(rows[i], HIGH);
    }
    // ---------

    // --------- CHANNELS READING
    for (int i = 0; i < MAX_CHANNELS; i++)
    {
      int reading = 1023 - analogRead(channels[i]);
      reading = map(reading <= CHANNEL_LOWER_LIMIT ? 0 : reading, 0, 1023, 0, 127);
      Serial.println(reading);
      event.channelValues[i] = reading;
    }
    // ---------

    // --------- MENU SWITCH READING
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
    // ---------

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
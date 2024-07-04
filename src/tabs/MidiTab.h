#pragma once

#include "config.h"
#include "Tab.h"
#include "State.h"
#include "midi.h"

class MidiTab : public Tab
{
public:
  void setup(State *state) {}

  void processInput(State *state, Input *input)
  {
    InputEvent event = input->process();

    for (int i = 0; i < MATRIX_LENGTH; i++)
    {
      if (!event.matrixButtonsChangeMask[i])
        continue;
      if (event.matrixButtonsHolding[i])
      {
#ifdef ENABLE_MIDI_LOGS
        Serial.print("b");
        Serial.println(i);
#endif
        noteOn(0, 60 + i, 127);
      }
      else
      {
#ifdef ENABLE_MIDI_LOGS
        Serial.print("!b");
        Serial.println(i);
#endif
        noteOff(0, 60 + i, 127);
      }
    }

    for (int i = 0; i < MAX_CHANNELS; i++)
    {
      if (!event.channelValuesChangeMask[i])
        continue;
      if (event.channelValues[i] > 0)
      {
#ifdef ENABLE_MIDI_LOGS
        Serial.print("c");
        Serial.print(i);
        Serial.print(" ");
        Serial.println(event.channelValues[i]);
#endif
        noteOn(0, 60 + i, event.channelValues[i]);
      }
      else
      {
#ifdef ENABLE_MIDI_LOGS
        Serial.print("!c");
        Serial.println(i);
#endif
        noteOff(0, 60 + i, 0);
      }
    }
  }

  void draw(State *state, Display *display)
  {
    display->clearDisplay();
    display->fillScreen(BLACK);
    display->setTextSize(2);
    display->setTextColor(WHITE);
    display->setCursor(0, SCREEN_HEIGHT / 2 - 10);
    display->print("MIDI Tab");
    display->display();
  }
};

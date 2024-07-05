#include "config.h"
#include "State.h"
#include "Input.h"
#include "midi.h"

State state;
Input input;

void setup()
{
  Serial.begin(9600);

  input.init();
}

void loop()
{
  input.sense();
  InputEvent event = input.process();

  bool isCc = event.menuSwitchPosition == 0;

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

  flushMidi();
}

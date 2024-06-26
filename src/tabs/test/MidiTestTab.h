#include "Tab.h"
#include "State.h"
#include "midi.h"

class MidiTestTab : public Tab
{
public:
  void setup(State *state) {}

  void processInput(State *state, Input *input)
  {
    InputEvent event = input->process();

    state->Mtt_previousNote = state->Mtt_midiNote;
    state->Mtt_midiNote += event.encoderDelta;
    bool shouldClearNotes = state->Mtt_sending && !event.encoderButton.holding;
    state->Mtt_sending = event.encoderButton.holding;

    if (shouldClearNotes)
    {
      noteOff(0, state->Mtt_previousNote, 127);
      noteOff(0, state->Mtt_midiNote, 127);
    }
    if (state->Mtt_sending)
    {
      if (state->Mtt_midiNote != state->Mtt_previousNote)
      {
        noteOff(0, state->Mtt_previousNote, 127);
      }
      noteOn(0, state->Mtt_midiNote, 127);
    }

    for (int i = 0; i < MATRIX_LENGTH; i++)
    {
      if (event.matrixButtonsHolding[i])
      {
        noteOn(0, 60 + i, 127);
      }
      else
      {
        noteOff(0, 60 + i, 127);
      }
    }

    for (int i = 0; i < MAX_CHANNELS; i++)
    {
      if (event.channelValues[i] > 0)
      {
        noteOn(0, 60 + i - 1, event.channelValues[i]);
        state->Mtt_channelValues[i] = event.channelValues[i];
      }
      else
      {
        noteOff(0, 60 + i - 1, 0);
      }
    }
  }

  void draw(State *state, Display *display)
  {
    display->fillScreen(BLACK);
    display->setTextSize(1);
    display->setTextColor(WHITE);
    display->setCursor(0, 0);
    display->print(MIDI_TEST_TAB_NAME);
    display->setCursor(0, 16);
    display->setTextSize(2);
    display->print("Note: ");
    display->println(state->Mtt_midiNote);
    display->print("Send: ");
    display->println(state->Mtt_sending ? "yes" : "no");
    for (int i = 0; i < MAX_CHANNELS; i++)
    {
      display->print(state->Mtt_channelValues[i]);
      display->print(" ");
    }
    display->display();
  }
};
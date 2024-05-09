#include "Tab.h"
#include "State.h"

class MatrixTestTab : public Tab
{
public:
  void setup(State *state) {}

  void processInput(State *state, Input *input)
  {
    InputEvent event = input->process();

    if (goBackOnHold(&event, state))
      return;

    for (int i = 0; i < MATRIX_LENGTH; i++)
    {
      state->Mxt_buttonsHolding[i] = event.matrixButtonsHolding[i];
    }
  }

  void draw(State *state, Display *display)
  {
    display->clearDisplay();
    display->fillScreen(BLACK);
    display->setTextSize(2);
    display->setTextColor(WHITE);
    for (int i = 0; i < MATRIX_HEIGHT; i++)
    {
      for (int j = 0; j < MATRIX_WIDTH; j++)
      {
        display->setCursor(j * 32, i * 18);
        display->print(state->Mxt_buttonsHolding[i * MATRIX_WIDTH + j]);
      }
    }
    display->display();
  }
};
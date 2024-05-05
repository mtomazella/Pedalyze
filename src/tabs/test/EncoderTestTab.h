#include "Tab.h"
#include "State.h"

class EncoderTestTab : public Tab
{
public:
  void setup(State *state) {}

  void processInput(State *state, Input *input)
  {
    InputEvent event = input->process();

    state->ETT_xOffset += event.encoderDelta;
    state->ETT_clicks += event.encoderButton.clicks;
    state->ETT_doubleClicks += event.encoderButton.doubleClicks;
    state->ETT_holdClicks += event.encoderButton.holdClicks;
    state->ETT_holding = event.encoderButton.holding;
    state->ETT_lastPress = event.encoderButton.lastPress;
    state->ETT_lastRelease = event.encoderButton.lastRelease;
  }

  void draw(State *state, Display *display)
  {
    display->clearDisplay();
    display->fillScreen(WHITE);
    display->setTextSize(1);
    display->setTextColor(BLACK);
    display->setCursor(0, 0);
    display->print(state->ETT_xOffset);
    display->fillCircle(SCREEN_WIDTH / 2 + state->ETT_xOffset, SCREEN_HEIGHT / 2, 10, BLACK);
    display->setCursor(0, 10);
    display->print("C: ");
    display->print(state->ETT_clicks);
    display->setCursor(0, 20);
    display->print("DC: ");
    display->print(state->ETT_doubleClicks);
    display->setCursor(0, 30);
    display->print("HC: ");
    display->print(state->ETT_holdClicks);
    display->setCursor(0, 40);
    display->print("H: ");
    display->print(state->ETT_holding);
    display->setCursor(0, 50);
    display->print("LP: ");
    display->print(state->ETT_lastPress);
    display->setCursor(0, 60);
    display->print("LR: ");
    display->print(state->ETT_lastRelease);
    display->display();
  }
};
#include "config.h"
#include "Display.h"
#include "Menu.h"
#include "Tab.h"
#include "State.h"
#include "Input.h"
#include "tabs/MidiTab.h"
#include "tabs/ControlTab.h"
#include "tabs/ConfigTab.h"

#ifdef ENABLE_TEST_TABS
#include "tabs/test/EncoderTestTab.h"
#include "tabs/test/MidiTestTab.h"
#include "tabs/test/MatrixTestTab.h"
#endif

Display display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
State state;
Menu menu;
Input input;

void setup()
{
  Serial.begin(9600);

  display.init(SCREEN_ADDRESS);

  display.setTextSize(2);
  display.fillScreen(WHITE);
  display.setTextColor(BLACK);
  display.setCursor(0, 28);
  display.println("PEDALYZE");
  display.display();

#ifdef ENABLE_TEST_TABS
  Tab *tabs[MAX_TABS] = {new ControlTab(), new MidiTab(), new ConfigTab(), new EncoderTestTab(), new MidiTestTab(), new MatrixTestTab()};
#else
  Tab *tabs[MAX_TABS] = {new ControlTab(), new MidiTab(), new ConfigTab()};
#endif

  menu.init(&state, tabs, MAX_TABS);
  input.init();
}

void loop()
{
  menu.loop();
  InputEvent inputEvent = input.sense();

  if (inputEvent.menuSwitchPositionChanged)
  { // allow for test tabs
    state.changeTab(inputEvent.menuSwitchPosition);
  }

  Tab *tab = menu.getCurrentTab();

  tab->processInput(&state, &input);

  if (menu.getCurrentTab()->shouldDraw(&state))
  {
    tab->draw(&state, &display);
  }
}

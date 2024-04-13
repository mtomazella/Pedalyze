#include "config.h"
#include "Display.h"
#include "Menu.h"
#include "Tab.h"
#include "State.h"
#include "Input.h"

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

  Tab *tabs[MAX_TABS] = {new TestTab()};

  menu.init(&state, tabs, MAX_TABS);
}

void loop()
{
  menu.loop();
  input.sense();

  Tab *tab = menu.getCurrentTab();

  tab->processInput(&state, &input);

  if (menu.getCurrentTab()->shouldDraw(&state))
  {
    tab->draw(&state, &display);
  }
}
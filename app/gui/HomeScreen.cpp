#include "HomeScreen.h"
#include "TempControl.h"
#include "Temperature.h"

HomeScreen::HomeScreen() : init_complete(false) {
  heat = new HomeWidget(0, 166, ILI9341_ORANGE);
  cool = new HomeWidget(82, 166, ILI9341_BLUE);
  wifi = new HomeWidget(164, 166, ILI9341_GREEN);
  settings = new HomeWidget(246, 166, ILI9341_OLIVE);
  temp2 = new HomeWidget(246, 83, ILI9341_MAROON);
  temp1 = new HomeWidget(246, 0, ILI9341_YELLOW);
}

void HomeScreen::init() {
  tft.fillScreen(ILI9341_BLACK);
  tft.fillRect(0, 0, 238, 157, ILI9341_GREENYELLOW);
  init_complete = true;
}

Screen* HomeScreen::touch() {
  return NULL;
}

void HomeScreen::update() {
  if (!init_complete)
    init();
  heat->update(true);
  temp1->update(true);
  settings->update(true);
  cool->update(true);
  temp2->update(true);
  wifi->update(true);

  tft.setCursor(10, 10);
  tft.setTextColor(ILI9341_WHITE, ILI9341_GREENYELLOW);
  tft.setTextSize(6);

  tft.print(rawTempToFString(tempControl.beerTemp()));

  tft.setCursor(10, 90);
  tft.print(rawTempToFString(tempControl.fridgeTemp()));
  tft.setTextColor(ILI9341_DARKGREY, ILI9341_GREENYELLOW);
  tft.setTextSize(3);
  tft.setCursor(200,10);
  tft.print('F');
  tft.setCursor(200,90);
  tft.print('F');
}

#include "GUI.h"
#include "TFT.h"
#include "HomeScreen.h"

GUI::GUI() {
  currentScreen = new HomeScreen();
}

GUI::~GUI() {
  delete currentScreen;
}

void GUI::update() {
  int16_t x = -1;
  int16_t y = -1;
  if (touchScreen.pressed()) {
    touchScreen.read();
    x = touchScreen.getX();
    y = touchScreen.getY();
  }

  Screen* nextScreen = currentScreen->touch(x, y);
  if (nextScreen) {
    delete currentScreen;
    currentScreen = nextScreen;
  }
  currentScreen->update();
}

void GUI::splash() {
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(28, 85);
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  tft.setTextSize(4);
  tft.print("fermenticle");
}

GUI gui;

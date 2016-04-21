#include "HomeScreen.h"
#include "TempControl.h"
#include "Temperature.h"

static bool heatActive() { return true; }
static bool coolActive() { return true; }
static bool wifiActive() { return true; }
static bool settingsActive() { return true; }
static bool fridgeSensorActive() { tempControl.fridgeSensorConnected(); }
static bool beerSensorActive() { return tempControl.beerSensorConnected(); }

static Screen* heatPressed() {
  return NULL;
}

static Screen* coolPressed() {
  return NULL;
}

static Screen* wifiPressed() {
  return NULL;
}

static Screen* settingsPressed() {
  return NULL;
}

static Screen* fridgeSensorPressed() {
  return NULL;
}

static Screen* beerSensorPressed() {
  return NULL;
}

HomeScreen::HomeScreen() : init_complete(false) {
  heat = new HomeWidget(0, 166, ILI9341_ORANGE, heatActive, heatPressed);
  cool = new HomeWidget(82, 166, ILI9341_BLUE, coolActive, coolPressed);
  wifi = new HomeWidget(164, 166, ILI9341_GREEN, wifiActive, wifiPressed);
  settings = new HomeWidget(246, 166, ILI9341_OLIVE, settingsActive, settingsPressed);
  fridgeSensor = new HomeWidget(246, 83, ILI9341_MAROON, fridgeSensorActive, fridgeSensorPressed);
  beerSensor = new HomeWidget(246, 0, ILI9341_YELLOW, beerSensorActive, beerSensorPressed);
  widgets.push_back(heat);
  widgets.push_back(cool);
  widgets.push_back(wifi);
  widgets.push_back(settings);
  widgets.push_back(fridgeSensor);
  widgets.push_back(beerSensor);
}

HomeScreen::~HomeScreen() {
  widgets.clear();
}

void HomeScreen::init() {
  tft.fillScreen(ILI9341_BLACK);
  tft.fillRect(0, 0, 238, 157, ILI9341_GREENYELLOW);
  init_complete = true;
}

Screen* HomeScreen::touch() {
  int16_t x = -1;
  int16_t y = -1;
  if (touchScreen.pressed()) {
    touchScreen.read();
    x = touchScreen.getX();
    y = touchScreen.getY();
  }

  for ( auto &widget : widgets ) {
    if (widget->contains(x, y)) {
      widget->press(true);
    } else {
      widget->press(false);
    }
    if (widget->justReleased())
      return widget->nextScreen();
  }

  return NULL;
}

void HomeScreen::update() {
  if (!init_complete)
    init();
  for ( auto &widget : widgets ) {
    widget->draw();
  }

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

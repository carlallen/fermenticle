#include "application.h"
#include "HomeScreen.h"
#include "TempControl.h"
#include "Temperature.h"
#include "WifiScreen.h"
#include "HardwareDeviceScreen.h"

static bool heatActive() { return tempControl.heating(); }
static bool coolActive() { return tempControl.cooling(); }
static bool wifiActive() { return WiFi.ready(); }
static bool settingsActive() { return true; }
static bool fridgeSensorActive() { return tempControl.fridgeSensorConnected(); }
static bool beerSensorActive() { return tempControl.beerSensorConnected(); }

void setHeater(HardwareDevice* device) {
  tempControl.setHeater(device);
}

void setChiller(HardwareDevice* device) {
  tempControl.setChiller(device);
}

static Screen* heatPressed() {
  return new HardwareDeviceScreen("Heater", ILI9341_ORANGE, &deviceList.outputPins, setHeater);
}

static Screen* coolPressed() {
  return new HardwareDeviceScreen("Chiller", ILI9341_BLUE, &deviceList.outputPins, setChiller);
}

static Screen* wifiPressed() {
  return new WifiScreen();
}

static Screen* settingsPressed() {
  return NULL;
}

static Screen* fridgeSensorPressed() {
  return NULL;
 // return new HardwareDeviceScreen("Chamber Temp", ILI9341_MAROON, &deviceList.tempDevices);
}

static Screen* beerSensorPressed() {
  return NULL;
  //return new HardwareDeviceScreen("Beer Temp", ILI9341_YELLOW, &deviceList.tempDevices);
}

HomeScreen::HomeScreen() : initialized(false) {
  buttons.push_back(new HomeWidget(0, 166, ILI9341_ORANGE, heatActive, heatPressed));
  buttons.push_back(new HomeWidget(82, 166, ILI9341_BLUE, coolActive, coolPressed));
  buttons.push_back(new HomeWidget(164, 166, ILI9341_GREEN, wifiActive, wifiPressed));
  buttons.push_back(new HomeWidget(246, 166, ILI9341_OLIVE, settingsActive, settingsPressed));
  buttons.push_back(new HomeWidget(246, 83, ILI9341_MAROON, fridgeSensorActive, fridgeSensorPressed));
  buttons.push_back(new HomeWidget(246, 0, ILI9341_YELLOW, beerSensorActive, beerSensorPressed));
}

HomeScreen::~HomeScreen() {
  buttons.clear();
}

void HomeScreen::init() {
  tft.fillScreen(ILI9341_BLACK);
  tft.fillRect(0, 0, 238, 157, ILI9341_GREENYELLOW);
  initialized = true;
}

Screen* HomeScreen::touch(int16_t x, int16_t y) {
  for ( auto &button : buttons ) {
    if (button->contains(x, y)) {
      button->press(true);
    } else {
      button->press(false);
    }
    if (button->justReleased())
      return button->nextScreen();
  }

  return NULL;
}

void HomeScreen::update() {
  if (!initialized)
    init();
  for ( auto &button : buttons ) {
    button->draw();
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

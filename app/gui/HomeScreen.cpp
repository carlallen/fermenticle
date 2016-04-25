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
static bool beerSensorActive() { return tempControl.beerSensor->connected(); }
static bool fridgeSensorActive() { return tempControl.fridgeSensor->connected(); }

static void setHeater(HardwareDevice* device) {
  tempControl.heater->setPinNumber(((OutputPinDevice*)device)->pinNumber());
}

static void setChiller(HardwareDevice* device) {
  tempControl.chiller->setPinNumber(((OutputPinDevice*)device)->pinNumber());
}

static void setBeerSensor(HardwareDevice* device) {
  tempControl.beerSensor->setAddress(((OneWireTempDevice*)device)->address);
}
static void setFridgeSensor(HardwareDevice* device) {
  tempControl.fridgeSensor->setAddress(((OneWireTempDevice*)device)->address);
}

static Screen* heatPressed() {
  return new HardwareDeviceScreen("Heater", HEATER_COLOR, &deviceList.outputPins, setHeater);
}

static Screen* coolPressed() {
  return new HardwareDeviceScreen("Chiller", CHILLER_COLOR, &deviceList.outputPins, setChiller);
}

static Screen* wifiPressed() {
  return new WifiScreen();
}

static Screen* settingsPressed() {
  return NULL;
}

static Screen* beerSensorPressed() {
  return new HardwareDeviceScreen("Beer Temp", BEER_SENSOR_COLOR, &deviceList.tempDevices, setBeerSensor);
}

static Screen* fridgeSensorPressed() {
 return new HardwareDeviceScreen("Chamber Temp", FRIDGE_SENSOR_COLOR, &deviceList.tempDevices, setFridgeSensor);
}

HomeScreen::HomeScreen() : initialized(false) {
  buttons.push_back(new HomeWidget(0, 166, HEATER_COLOR, heatActive, heatPressed));
  buttons.push_back(new HomeWidget(82, 166, CHILLER_COLOR, coolActive, coolPressed));
  buttons.push_back(new HomeWidget(164, 166, WIFI_COLOR, wifiActive, wifiPressed));
  buttons.push_back(new HomeWidget(246, 166, SETTINGS_COLOR, settingsActive, settingsPressed));
  buttons.push_back(new HomeWidget(246, 83, FRIDGE_SENSOR_COLOR, fridgeSensorActive, fridgeSensorPressed));
  buttons.push_back(new HomeWidget(246, 0, BEER_SENSOR_COLOR, beerSensorActive, beerSensorPressed));
}

HomeScreen::~HomeScreen() {
  for ( auto &button : buttons ) {
    delete button;
  }
  buttons.clear();
}

void HomeScreen::init() {
  tft.fillScreen(ILI9341_BLACK);
  tft.fillRect(0, 0, 238, 157, TEMP_PANEL_COLOR);
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
  tft.setTextColor(ILI9341_WHITE, TEMP_PANEL_COLOR);
  tft.setTextSize(6);

  tft.print(rawTempToFString(tempControl.beerTemp()));

  tft.setCursor(10, 90);
  tft.print(rawTempToFString(tempControl.fridgeTemp()));
  tft.setTextColor(ILI9341_DARKGREY, TEMP_PANEL_COLOR);
  tft.setTextSize(3);
  tft.setCursor(200,10);
  tft.print('F');
  tft.setCursor(200,90);
  tft.print('F');
}

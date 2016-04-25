#include "HardwareDeviceScreen.h"
#include "HomeScreen.h"

HardwareDeviceScreen::HardwareDeviceScreen(String name, int16_t deviceColor,
                                           std::vector<HardwareDevice*> *devices,
                                           setHardwareCallback setHardware) : ok_btn(110, 100, "OK") {
  this->name = name;
  this->deviceColor = deviceColor;
  touched = false;
  initialized = false;
  this->devices = devices;
  this->setHardware = setHardware;
  deviceList.refreshDeviceList();
}

HardwareDeviceScreen::~HardwareDeviceScreen() {
  clear();
}

void HardwareDeviceScreen::clear() {
  for ( auto &button : outputButtons ) {
    delete button;
  }
  outputButtons.clear();
}

void HardwareDeviceScreen::init() {
  std::vector<HardwareDevice*>::iterator d_iter = devices->begin();
  int16_t x_pos = 0;
  int16_t y_pos = 40;
  for(int i = 0; i < 8 && d_iter < devices->end(); i++) {
    if (i == 4) {
      x_pos = 0;
      y_pos = 123;
    }
    outputButtons.push_back(new HardwareDeviceButton(x_pos, y_pos, *d_iter, setHardware));
    x_pos += 82;
    d_iter++;
  }
  tft.fillScreen(ILI9341_BLACK);
  tft.fillRect(0, 0, 320, 30, deviceColor);
  String title = name + " Settings";
  tft.setCursor(0 + 160 - title.length()*6, 7);
  tft.setTextColor(ILI9341_WHITE, deviceColor);
  tft.setTextSize(2);
  tft.print(title);
  initialized = true;
}

Screen* HardwareDeviceScreen::touch(int16_t x, int16_t y) {
  for ( auto &button : outputButtons ) {
    if (button->contains(x, y)) {
      button->press(true);
    } else {
      button->press(false);
    }
    if (button->justReleased()) {
      button->select();
      resetButtons();
    }
  }
  if (ok_btn.contains(x, y)) {
    ok_btn.press(true);
  } else {
    ok_btn.press(false);
  }
  if (ok_btn.justReleased())
    return new HomeScreen();

  return NULL;
}

void HardwareDeviceScreen::update() {
  if (!initialized)
    init();
  for ( auto &button : outputButtons ) {
    button->draw();
  }
  ok_btn.draw();
}

void HardwareDeviceScreen::resetButtons() {
  deviceList.refreshDeviceConnections();
  for ( auto &button : outputButtons ) {
    button->init();
  }
}

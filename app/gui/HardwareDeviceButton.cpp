#include "HardwareDeviceButton.h"
#include "TFT.h"
#include "HomeScreen.h"

HardwareDeviceButton::HardwareDeviceButton(int16_t x, int16_t y, HardwareDevice* device, setHardwareCallback setHardware) : Touchable() {
  _x = x;
  _y = y;
  initialized = false;
  this->device = device;
  this->setHardware = setHardware;
}

bool HardwareDeviceButton::contains(int16_t x, int16_t y) {
  if (x < _x || (x > (_x + HARDWARE_BUTTON_WIDTH))) return false;
  if (y < _y || (y > (_y + HARDWARE_BUTTON_HEIGHT))) return false;
  return true;
}

void HardwareDeviceButton::init() {
  initialized = true;
  tft.fillRect(_x, _y, HARDWARE_BUTTON_WIDTH, HARDWARE_BUTTON_HEIGHT, background_color());
}

void HardwareDeviceButton::select() {
  if (device->canSelect()) {
    setHardware(device);
  }
}

void HardwareDeviceButton::draw() {
  if (!initialized)
    init();

  if (justPressed() || justReleased())
    tft.fillRect(_x, _y, HARDWARE_BUTTON_WIDTH, HARDWARE_BUTTON_HEIGHT, background_color());

  String text = device->value();
  int16_t x_pos = _x + ((HARDWARE_BUTTON_WIDTH/2)-(text.length()*6));
  tft.setCursor(x_pos, _y+29);
  tft.setTextColor(ILI9341_WHITE, background_color());
  tft.setTextSize(2);
  tft.print(text);

  text = device->label();
  x_pos = _x + ((HARDWARE_BUTTON_WIDTH/2)-(text.length()*3));
    tft.setCursor(x_pos, _y+10);
  tft.setTextSize(1);
  tft.print(text);
}


int16_t HardwareDeviceButton::background_color() {
  if (device->canSelect() && isPressed())
    return ILI9341_BLACK;
  return device->background_color();
}

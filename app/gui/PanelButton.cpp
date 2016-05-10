#include "PanelButton.h"

PanelButton::PanelButton(uint8_t row, uint8_t column, int16_t color) : Touchable() {
  _init(row, column, color, 40);
}

PanelButton::PanelButton(uint8_t row, uint8_t column, int16_t color, int16_t row_offset) : Touchable() {
  _init(row, column, color, row_offset);
}

void PanelButton::_init(uint8_t row, uint8_t column, int16_t color, int16_t row_offset) {
  this->_y = row_offset + 83*row;
  this->_x = 82*column;
  this->_color = color;
  initialized = false;
}

bool PanelButton::contains(int16_t x, int16_t y) {
  if (x < _x || (x > (_x + PANEL_BUTTON_SIZE))) return false;
  if (y < _y || (y > (_y + PANEL_BUTTON_SIZE))) return false;
  return true;
}

void PanelButton::draw() {
  if (!initialized || justPressed() || justReleased()) {
    tft.fillRect(_x, _y, PANEL_BUTTON_SIZE, PANEL_BUTTON_SIZE, color());
    initialized = true;
  }
}

int16_t PanelButton::color() {
  if (isPressed())
    return ILI9341_BLACK;
  else
    return _color;
}

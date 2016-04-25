#include "HomeWidget.h"

HomeWidget::HomeWidget(int16_t x, int16_t y, int16_t activeColor,
    WidgetActiveCallback active,
    ScreenCallback nextScreen) {
    this->active = active;
    this->_nextScreen = nextScreen;
    this->activeColor = activeColor;
    last_active = false;
    initialized = false;
    _x = x;
    _y = y;
  }

void HomeWidget::draw() {
  if (!initialized || justPressed() || justReleased() || last_active != active()) {
    tft.fillRect(_x, _y, HOME_WIDGET_WIDTH, HOME_WIDGET_HEIGHT, backgroundColor());
    initialized = true;
  }
  last_active = active();
}

bool HomeWidget::contains(int16_t x, int16_t y) {
  if (x < _x || (x > (_x + HOME_WIDGET_WIDTH))) return false;
  if (y < _y || (y > (_y + HOME_WIDGET_HEIGHT))) return false;
  return true;
}

Screen* HomeWidget::nextScreen() {
  return _nextScreen();
}

int16_t HomeWidget::backgroundColor() {
  if (isPressed())
    return ILI9341_BLACK;
  if (active()) {
    return activeColor;
  } else {
    return INACTIVE_COLOR;
  }
}

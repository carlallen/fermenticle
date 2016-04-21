#include "HomeWidget.h"

HomeWidget::HomeWidget(int16_t x, int16_t y, int16_t activeColor,
    WidgetActiveCallback active,
    ScreenCallback nextScreen): _x(x), _y(y), activeColor(activeColor), init_complete(false) {
    this->active = active;
    this->nextScreen = nextScreen;
  }

void HomeWidget::init() {
  init_complete = true;
  last_active = false;
  laststate = currstate = false;
  tft.fillRect(_x, _y, HOME_WIDGET_WIDTH, HOME_WIDGET_HEIGHT, ILI9341_DARKGREY);
}


void HomeWidget::draw() {
  if (!init_complete)
    init();

  if (isPressed()) {
    tft.fillRect(_x, _y, HOME_WIDGET_WIDTH, HOME_WIDGET_HEIGHT, ILI9341_BLACK);
    return;
  }
  if (active() != this->last_active || justReleased()) {
    if (active()) {
      tft.fillRect(_x, _y, HOME_WIDGET_WIDTH, HOME_WIDGET_HEIGHT, activeColor);
    } else {
      tft.fillRect(_x, _y, HOME_WIDGET_WIDTH, HOME_WIDGET_HEIGHT, ILI9341_DARKGREY);
    }
  }
  this->last_active = active();
}

void HomeWidget::press(bool p) {
  laststate = currstate;
  currstate = p;
}

bool HomeWidget::contains(int16_t x, int16_t y) {
  if (x < _x || (x > (_x + HOME_WIDGET_WIDTH))) return false;
  if (y < _y || (y > (_y + HOME_WIDGET_HEIGHT))) return false;
  return true;
}

bool HomeWidget::isPressed() { return currstate; }
bool HomeWidget::justPressed() { return (currstate && !laststate); }
bool HomeWidget::justReleased() { return (!currstate && laststate); }

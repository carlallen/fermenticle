#pragma once
#include "TFT.h"
#define HOME_WIDGET_WIDTH 74
#define HOME_WIDGET_HEIGHT 74
class HomeWidget
{
public:
  HomeWidget(int16_t x, int16_t y, int16_t activeColor): x(x), y(y), activeColor(activeColor), init_complete(false) {} ;
  ~HomeWidget() {};
  void init() {
    init_complete = true;
    active = false;
    tft.fillRect(x, y, HOME_WIDGET_WIDTH, HOME_WIDGET_HEIGHT, ILI9341_DARKGREY);
  }
  void update(bool active) {
    if (!init_complete)
      init();

    if (active != this->active) {
      if (active) {
        tft.fillRect(x, y, HOME_WIDGET_WIDTH, HOME_WIDGET_HEIGHT, activeColor);
      } else {
        tft.fillRect(x, y, HOME_WIDGET_WIDTH, HOME_WIDGET_HEIGHT, ILI9341_DARKGREY);
      }
    }
    this->active = active;
  }

private:
  bool active;
  bool init_complete;
  int16_t x;
  int16_t y;
  int16_t activeColor;
};

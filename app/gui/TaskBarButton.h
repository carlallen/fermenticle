#pragma once
#include "Touchable.h"
#include "TFT.h"

class TaskBarButton : public Touchable
{
public:
  TaskBarButton(int16_t x, int16_t w, String text) {
    _x = x;
    _w = w;
    _text = text;
    initialized = false;
  }
  ~TaskBarButton() {}
  int16_t background_color() {
    if (isPressed()) {
      return ILI9341_LIGHTGREY;
    } else {
      return ILI9341_NAVY;
    }
  }

  void draw() {
    if (!initialized || justPressed() || justReleased()) {
      tft.fillRect(_x, 206, _w, 34, background_color());
      initialized = true;
    }
    int16_t x_pos = _x + ((_w/2)-(_text.length()*6));
    tft.setCursor(x_pos, 218);
    tft.setTextColor(ILI9341_WHITE, background_color());
    tft.setTextSize(2);
    tft.print(_text);
  }

  bool contains(int16_t x, int16_t y) {
    if (x < _x || (x > (_x + _w))) return false;
    if (y < 206 || (y > (240))) return false;
    return true;
  }
private:
  int16_t _x, _w;
  bool initialized;
  String _text;
};

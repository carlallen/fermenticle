#pragma once
#include "Touchable.h"
#include "TFT.h"
#include "Screen.h"
#define HOME_WIDGET_WIDTH 74
#define HOME_WIDGET_HEIGHT 74

typedef bool (*WidgetActiveCallback)();
typedef Screen* (*ScreenCallback)();

class HomeWidget : public Touchable
{
public:
  HomeWidget(int16_t x, int16_t y, int16_t activeColor, WidgetActiveCallback active, ScreenCallback nextScreen);
  ~HomeWidget() {};
  void init();
  void draw();
  bool contains(int16_t _x, int16_t _y);
  Screen* nextScreen() { return _nextScreen(); };

private:
  ScreenCallback _nextScreen;
  WidgetActiveCallback active;
  bool last_active;
  bool initialized;
  int16_t _x;
  int16_t _y;
  int16_t activeColor;
};

#pragma once
#include "TFT.h"
#include "Screen.h"
#define HOME_WIDGET_WIDTH 74
#define HOME_WIDGET_HEIGHT 74

typedef bool (*WidgetActiveCallback)();
typedef Screen* (*ScreenCallback)();

class HomeWidget
{
public:
  HomeWidget(int16_t x, int16_t y, int16_t activeColor, WidgetActiveCallback active, ScreenCallback nextScreen);
  ~HomeWidget() {};
  void init();
  void draw();

  void press(bool p);
  bool contains(int16_t _x, int16_t _y);
  bool isPressed();
  bool justPressed();
  bool justReleased();
  ScreenCallback nextScreen;

private:
  WidgetActiveCallback active;
  bool last_active;
  bool init_complete;
  int16_t _x;
  int16_t _y;
  int16_t activeColor;
  bool currstate, laststate;
};

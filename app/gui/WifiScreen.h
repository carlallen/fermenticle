#pragma once
#include <vector>
#include "Screen.h"
#include "TaskBarButton.h"
class WifiScreen : public Screen
{
public:
  WifiScreen();
  ~WifiScreen();
  Screen* touch(int16_t x, int16_t y);
  void update();
protected:
  void init();
  bool initialized;
  bool touched;
  uint8_t update_delay;
  TaskBarButton ok_btn;
};

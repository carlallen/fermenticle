#pragma once
#include <vector>
#include "Screen.h"
#include "HomeWidget.h"
class HomeScreen : public Screen
{
public:
  HomeScreen();
  ~HomeScreen();

  void init();
  Screen* touch(int16_t x, int16_t y);
  void update();
private:
  bool initialized;
  std::vector<HomeWidget*> buttons;
};

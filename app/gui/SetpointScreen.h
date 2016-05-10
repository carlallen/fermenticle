#pragma once
#include "Screen.h"
#include "TaskBarButton.h"
#include "PanelButton.h"
#include <vector>
class SetpointScreen : public Screen
{
public:
  SetpointScreen();
  ~SetpointScreen() {};
  Screen* touch(int16_t x, int16_t y);
  void update();
protected:
  void init();
  bool initialized;
  TaskBarButton ok_btn;
  PanelButton up_button;
  PanelButton down_button;
  std::vector<Touchable*> buttons;
};

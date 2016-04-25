#pragma once
#include "Screen.h"
#include <vector>
#include "HardwareDeviceButton.h"
#include "DeviceList.h"
#include "TaskBarButton.h"

class HardwareDeviceScreen : public Screen
{
public:
  HardwareDeviceScreen(String name, int16_t deviceColor, std::vector<HardwareDevice*> *devices, setHardwareCallback setHardware);
  ~HardwareDeviceScreen();
  Screen* touch(int16_t x, int16_t y);
  void update();
protected:
  void init();
  void clear();
  void resetButtons();
  bool initialized;
  int16_t deviceColor;
  String name;
  bool touched;
  std::vector<HardwareDevice*> *devices;
  std::vector<HardwareDeviceButton*> outputButtons;
  setHardwareCallback setHardware;
  TaskBarButton ok_btn;
};

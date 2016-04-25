#pragma once
#include "Screen.h"
#include "Touchable.h"
#include "DeviceList.h"
#define HARDWARE_BUTTON_WIDTH 74
#define HARDWARE_BUTTON_HEIGHT 74

typedef void (*setHardwareCallback)(HardwareDevice*);

class HardwareDeviceButton : public Touchable
{
public:
  HardwareDeviceButton(int16_t x, int16_t y, HardwareDevice* device, setHardwareCallback setHardware);
  ~HardwareDeviceButton() {}
  void init();
  void draw();
  bool contains(int16_t _x, int16_t _y);
  void select();
protected:
  bool initialized;
  bool currstate, laststate;
  int16_t _x;
  int16_t _y;
  HardwareDevice* device;
  setHardwareCallback setHardware;
  int16_t background_color();
};

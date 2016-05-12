#pragma once
#include "application.h"
#include "OutputDevice.h"

class OutputDeviceManager
{
public:
  OutputDeviceManager();
  ~OutputDeviceManager();
  void init();
  bool heating();
  bool cooling();
  void heat();
  void cool();
  void idle();
  OutputDevice *heater;
  OutputDevice *chiller;
};
extern OutputDeviceManager outputDeviceMgr;

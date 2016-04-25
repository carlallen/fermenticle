#pragma once
#include "application.h"
#include "Sensor.h"
#include "OutputDevice.h"

class TempControl
{
public:
  TempControl();
  ~TempControl();
  void init();
  int16_t beerTemp();
  int16_t fridgeTemp();
  bool heating();
  bool cooling();
  void updateSensors();
  Sensor *beerSensor;
  Sensor *fridgeSensor;
  OutputDevice *heater;
  OutputDevice *chiller;
};
extern TempControl tempControl;

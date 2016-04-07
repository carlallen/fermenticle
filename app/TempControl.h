#pragma once
#include "application.h"
#include "Sensor.h"

class TempControl
{
public:
  TempControl();
  ~TempControl();
  void init();
  int16_t beerTemp();
  int16_t fridgeTemp();
  void setBeerAddress(OneWireAddress address);
  void updateSensors();
private:
  Sensor *beerSensor;
  Sensor *fridgeSensor;
};
extern TempControl tempControl;

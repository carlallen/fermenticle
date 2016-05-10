#pragma once
#include "application.h"
#include "OneWireAddress.h"
#include "Temperature.h"
class Sensor
{
public:
  Sensor();
  ~Sensor() {};
  void init();
  RawTemperature temp();
  bool connected() { return deviceConnected; };
  void setAddress(OneWireAddress address);
  void update();
  OneWireAddress address;
private:
  bool deviceConnected;
  RawTemperature sample;
  void clearAddress();
};

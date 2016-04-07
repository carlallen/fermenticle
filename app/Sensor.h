#pragma once
#include "application.h"
#include "OneWireAddress.h"
class Sensor
{
public:
  Sensor();
  ~Sensor() {};
  void init();
  int16_t temp();
  bool connected() { return deviceConnected; };
  void setAddress(OneWireAddress address);
  void update();
  void requestTemperatures();
private:
  bool deviceConnected;
  int16_t sample;
  OneWireAddress address;
};

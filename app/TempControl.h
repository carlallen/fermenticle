#pragma once
#include "application.h"
#include "Sensor.h"
#include "OutputDevice.h"
#include "DeviceList.h"

class TempControl
{
public:
  TempControl();
  ~TempControl();
  void init();
  int16_t beerTemp();
  int16_t fridgeTemp();
  void setBeerAddress(OneWireAddress address);
  void setFridgeAddress(OneWireAddress address);
  bool beerSensorConnected();
  bool fridgeSensorConnected();
  bool heating();
  bool cooling();
  void updateSensors();
  void setHeater(HardwareDevice* device);
  void setChiller(HardwareDevice* device);
  Sensor *beerSensor;
  Sensor *fridgeSensor;
  OutputDevice *heater;
  OutputDevice *chiller;
};
extern TempControl tempControl;

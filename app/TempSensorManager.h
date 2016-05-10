#pragma once
#include "Sensor.h"
#include "Temperature.h"
#include "DeviceList.h"
#include "EEPROM_Manager.h"
class TempSensorManager
{
public:
  TempSensorManager();
  ~TempSensorManager() {};
  void init();
  void updateSensors();
  RawTemperature fridgeTemp();
  RawTemperature beerTemp();
  bool beerSensorConnected();
  bool fridgeSensorConnected();
  Sensor beerSensor;
  Sensor fridgeSensor;
};

extern TempSensorManager tempSensorMgr;

// Callback methods for home screen
static void setBeerSensor(HardwareDevice* device) {
  tempSensorMgr.beerSensor.setAddress(((OneWireTempDevice*)device)->address);
  save_eeprom();
}
static void setFridgeSensor(HardwareDevice* device) {
  tempSensorMgr.fridgeSensor.setAddress(((OneWireTempDevice*)device)->address);
  save_eeprom();
}


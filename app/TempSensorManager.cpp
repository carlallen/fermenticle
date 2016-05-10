#include "TempSensorManager.h"
#include "GlobalOneWire.h"

TempSensorManager::TempSensorManager() : beerSensor(), fridgeSensor() { }

void TempSensorManager::init() {
  dallas->requestTemperatures();
}

void TempSensorManager::updateSensors() {
  beerSensor.update();
  fridgeSensor.update();
}

RawTemperature TempSensorManager::fridgeTemp() {
  return fridgeSensor.temp();
}

RawTemperature TempSensorManager::beerTemp() {
  return beerSensor.temp();
}

bool TempSensorManager::beerSensorConnected() {
  beerSensor.connected();
}

bool TempSensorManager::fridgeSensorConnected() {
  fridgeSensor.connected();
}

TempSensorManager tempSensorMgr;

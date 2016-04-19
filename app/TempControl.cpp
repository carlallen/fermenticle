#include "TempControl.h"

TempControl::TempControl() {
  beerSensor = new Sensor();
  fridgeSensor = new Sensor();
}

TempControl::~TempControl() {
  delete beerSensor;
  delete fridgeSensor;
}

void TempControl::init() {
  beerSensor->init();
  fridgeSensor->init();
}

void TempControl::updateSensors() {
  beerSensor->update();
  fridgeSensor->update();
}

int16_t TempControl::beerTemp() {
  return beerSensor->temp();
}

int16_t TempControl::fridgeTemp() {
  return fridgeSensor->temp();
}

void TempControl::setBeerAddress(OneWireAddress address) {
  beerSensor->setAddress(address);
}

void TempControl::setFridgeAddress(OneWireAddress address) {
  fridgeSensor->setAddress(address);
}
bool TempControl::beerSensorConnected() {
  return beerSensor->connected();
}
bool TempControl::fridgeSensorConnected() {
  return fridgeSensor->connected();
}

TempControl tempControl;

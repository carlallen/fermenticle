#include "OutputDeviceManager.h"

OutputDeviceManager::OutputDeviceManager() {
  heater = new OutputDevice();
  chiller = new OutputDevice();
}

OutputDeviceManager::~OutputDeviceManager() {
  delete heater;
  delete chiller;
}

void OutputDeviceManager::init() {
}

void OutputDeviceManager::heat() {
  heater->turnOn();
  chiller->turnOff();
}

void OutputDeviceManager::cool() {
  heater->turnOff();
  chiller->turnOn();
}

void OutputDeviceManager::idle() {
  heater->turnOff();
  chiller->turnOff();
}

bool OutputDeviceManager::heating() {
  return heater->isOn();
}

bool OutputDeviceManager::cooling() {
  return chiller->isOn();
}

OutputDeviceManager outputDeviceMgr;

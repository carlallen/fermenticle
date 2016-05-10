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

bool OutputDeviceManager::heating() {
  return heater->isOn();
}

bool OutputDeviceManager::cooling() {
  return chiller->isOn();
}

OutputDeviceManager outputDeviceMgr;

#include "DeviceList.h"
#include "GlobalOneWire.h"
#include "TempControl.h"

DeviceList::DeviceList() {
}

DeviceList::~DeviceList() {
 clear();
}

void DeviceList::clear() {
  for ( auto &device : outputPins ) {
    delete device;
  }
  for (auto &device : tempDevices) {
    delete device;
  }
  tempDevices.clear();
  outputPins.clear();
}

void DeviceList::refreshDeviceList() {
  clear();
  OneWireAddress address;
  ow->reset_search();
  while(ow->search(address)) {
    tempDevices.push_back(new OneWireTempDevice(address));
  }
  outputPins.push_back(new OutputPinDevice(A7, "DO0"));
  outputPins.push_back(new OutputPinDevice(A6, "DO3"));
  outputPins.push_back(new OutputPinDevice(A1, "DO2"));
  outputPins.push_back(new OutputPinDevice(A0, "DO1"));
  refreshDeviceConnections();
}

void DeviceList::refreshDeviceConnections() {
  markOutputPins();
  markSensorDevices();
}

void DeviceList::markOutputPins() {
  for ( auto &device : outputPins ) {
    ((OutputPinDevice*)device)->setOutputType(NO_OUTPUT);
    if (((OutputPinDevice*)device)->pinNumber() == tempControl.heater->pinNumber())
      ((OutputPinDevice*)device)->setOutputType(HEAT);
    if (((OutputPinDevice*)device)->pinNumber() == tempControl.chiller->pinNumber())
      ((OutputPinDevice*)device)->setOutputType(COOL);
  }
}

void DeviceList::markSensorDevices() {
  for ( auto &device : tempDevices ) {
    ((OneWireTempDevice*)device)->setSensorType(NO_SENSOR);
    if (addressesMatch(((OneWireTempDevice*)device)->address, tempControl.beerSensor->address))
      ((OneWireTempDevice*)device)->setSensorType(BEER);
    if (addressesMatch(((OneWireTempDevice*)device)->address, tempControl.fridgeSensor->address))
      ((OneWireTempDevice*)device)->setSensorType(FRIDGE);
  }
}

DeviceList deviceList;

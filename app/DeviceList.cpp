#include "DeviceList.h"
#include "GlobalOneWire.h"
#include "TempControl.h"

DeviceList::DeviceList() {
}

DeviceList::~DeviceList() {
 clear();
}

void DeviceList::clear() {
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
  outputPins.push_back(new OutputPinDevice(A7, NONE, "DO0"));
  outputPins.push_back(new OutputPinDevice(A0, NONE, "DO1"));
  outputPins.push_back(new OutputPinDevice(A1, NONE, "DO2"));
  outputPins.push_back(new OutputPinDevice(A6, NONE, "DO3"));
  markOutputPins();
}

void DeviceList::markOutputPins() {
  for ( auto &device : outputPins ) {
    if (((OutputPinDevice*)device)->pinNumber() == tempControl.heater->pinNumber()) {
      ((OutputPinDevice*)device)->setOutputType(HEAT);
    }
    if (((OutputPinDevice*)device)->pinNumber() == tempControl.chiller->pinNumber()) {
      ((OutputPinDevice*)device)->setOutputType(COOL);
    }
  }
}

DeviceList deviceList;

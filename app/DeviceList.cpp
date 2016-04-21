#include "DeviceList.h"
#include "GlobalOneWire.h"

DeviceList::DeviceList() {
  outputDevices.emplace_back(OutputDevice{0, NONE});
  outputDevices.emplace_back(OutputDevice{1, NONE});
  outputDevices.emplace_back(OutputDevice{2, NONE});
  outputDevices.emplace_back(OutputDevice{3, NONE});
}

DeviceList::~DeviceList() {
 tempDevices.clear();
 outputDevices.clear();
}

void DeviceList::refreshDeviceList() {
  tempDevices.clear();
  OneWireDevice device;
  device.lastTemp = DEVICE_DISCONNECTED_RAW;
  ow->reset_search();
  while(ow->search(device.address)) {
    Serial.println(addressToString(device.address));
    tempDevices.push_back(device);
  }
}
DeviceList deviceList;

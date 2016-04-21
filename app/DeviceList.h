#pragma once
#include <vector>
#include "OneWireAddress.h"
#include "application.h"

typedef enum {
  NONE,
  HEAT,
  COOL
} OutputType;

struct OneWireDevice {
  OneWireAddress address;
  int16_t lastTemp;
};

struct OutputDevice {
  uint8_t pinNumber;
  OutputType type;
};

class DeviceList
{
public:
  DeviceList();
  ~DeviceList();
  std::vector<OneWireDevice> tempDevices;
  std::vector<OutputDevice> outputDevices;
  void refreshDeviceList();
};
extern DeviceList deviceList;

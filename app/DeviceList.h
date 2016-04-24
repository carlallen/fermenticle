#pragma once
#include <vector>
#include "OneWireAddress.h"
#include "application.h"
#include "Temperature.h"

typedef enum {
  NONE,
  HEAT,
  COOL
} OutputType;

class HardwareDevice
{
public:
  HardwareDevice() {}
  ~HardwareDevice() {}
  virtual String label();
  virtual String value();
  virtual bool canSelect();
};

class OneWireTempDevice : public HardwareDevice
{
public:
  OneWireTempDevice(OneWireAddress address) {
    memcpy(this->address, address, 8);
    lastTemp = DEVICE_DISCONNECTED_RAW;
  }
  ~OneWireTempDevice() {}
  String label() { return addressToString(address); }
  String value() { return rawTempToFString(lastTemp); }
  void setLastTemp(int16_t temp) { lastTemp = temp; }
  OneWireAddress address;
  bool canSelect() { return true; }
private:
  int16_t lastTemp;
};

class OutputPinDevice : public HardwareDevice
{
public:
  OutputPinDevice(uint8_t pinNumber, OutputType type, String label) : _pinNumber(pinNumber), type(type), _label(label) {}
  ~OutputPinDevice() {}
  String value() { return _label; }
  String label() {
    switch (type) {
      case HEAT:
        return "HEAT";
      case COOL:
        return "COOL";
      default:
        return "";
    }
  }
  bool canSelect() { return type == NONE; }
  void setOutputType(OutputType type) { this->type = type; }
  uint8_t pinNumber() { return _pinNumber; }
private:
  uint8_t _pinNumber;
  OutputType type;
  String _label;
};

class DeviceList
{
public:
  DeviceList();
  ~DeviceList();
  std::vector<HardwareDevice*> tempDevices;
  std::vector<HardwareDevice*> outputPins;
  void clear();
  void refreshDeviceList();
private:
  void markOutputPins();
};
extern DeviceList deviceList;

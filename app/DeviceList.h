#pragma once
#include <vector>
#include "OneWireAddress.h"
#include "application.h"
#include "Temperature.h"
#include "TFT.h"

typedef enum {
  NO_OUTPUT,
  HEAT,
  COOL
} OutputType;

typedef enum {
  NO_SENSOR,
  BEER,
  FRIDGE,
} SensorType;

class HardwareDevice
{
public:
  HardwareDevice() {}
  virtual ~HardwareDevice() {}
  virtual String label() = 0;
  virtual String value() = 0;
  virtual bool canSelect() = 0;
  virtual int16_t background_color() = 0;
};

class OneWireTempDevice : public HardwareDevice
{
public:
  OneWireTempDevice(OneWireAddress address) {
    type = NO_SENSOR;
    memcpy(this->address, address, 8);
    lastTemp = DEVICE_DISCONNECTED_RAW;
  }
  ~OneWireTempDevice() {}
  String label() { return addressToString(address).substring(4); }
  String value() { return rawTempToFString(lastTemp); }
  void setLastTemp(int16_t temp) { lastTemp = temp; }
  OneWireAddress address;
  bool canSelect() { return type == NO_SENSOR; }
  void setSensorType(SensorType type) { this->type = type; }
  int16_t background_color() {
    switch (type) {
      case BEER:
        return BEER_SENSOR_COLOR;
      case FRIDGE:
        return FRIDGE_SENSOR_COLOR;
      default:
        return INACTIVE_COLOR;
    }
  }
private:
  int16_t lastTemp;
  SensorType type;
};

class OutputPinDevice : public HardwareDevice
{
public:
  OutputPinDevice(uint8_t pinNumber, String label) : _pinNumber(pinNumber), _label(label) {
    type = NO_OUTPUT;
  }
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
  int16_t background_color() {
    switch (type) {
      case HEAT:
        return HEATER_COLOR;
      case COOL:
        return CHILLER_COLOR;
      default:
        return INACTIVE_COLOR;
    }
  }
  bool canSelect() { return type == NO_OUTPUT; }
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
  void refreshDeviceConnections();
private:
  void markOutputPins();
  void markSensorDevices();
};
extern DeviceList deviceList;

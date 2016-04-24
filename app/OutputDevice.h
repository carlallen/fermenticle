#pragma once
#include "application.h"

class OutputDevice
{
public:
  OutputDevice();
  ~OutputDevice();
  void setPinNumber(uint8_t pinNumber);
  void turnOn();
  void turnOff();
  bool isConfigured() { return configured; }
  bool isOn() { return on; }
  uint8_t pinNumber() { return _pinNumber; }
private:
  uint8_t _pinNumber;
  bool on;
  bool configured;
};

#include "OutputDevice.h"

OutputDevice::OutputDevice() {
  on = false;
  configured = false;
  _pinNumber = 0;
}
OutputDevice::~OutputDevice() { }

void OutputDevice::setPinNumber(uint8_t pinNumber) {
  turnOff();
  configured = true;
  pinMode(pinNumber, OUTPUT);
  _pinNumber = pinNumber;
}

void OutputDevice::turnOn() {
  if (configured) {
    digitalWrite(_pinNumber, 1);
  }
}

void OutputDevice::turnOff() {
  if (configured) {
    digitalWrite(_pinNumber, 0);
  }
}

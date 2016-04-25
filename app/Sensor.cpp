#include "Sensor.h"
#include "GlobalOneWire.h"

Sensor::Sensor() : deviceConnected(false), sample(DEVICE_DISCONNECTED_RAW) {
  clearAddress();
}

void Sensor::init() {
  requestTemperatures();
}

int16_t Sensor::temp() {
  if (connected()) {
    return sample;
  } else {
    return DEVICE_DISCONNECTED_RAW;
  }
}
void Sensor::setAddress(OneWireAddress address) {
  memcpy(this->address, address, sizeof(OneWireAddress));
}
void Sensor::update() {
  if (address)
    sample = dallas->getTemp(address);
  if (sample == DEVICE_DISCONNECTED_RAW)
    deviceConnected = false;
  else
    deviceConnected = true;
  requestTemperatures();
}

void Sensor::requestTemperatures() {
  if (address)
    dallas->requestTemperaturesByAddress(address);
}

void Sensor::clearAddress() {
  for(int i = 0; i < 8; i++) {
    address[i] = 0;
  }
}

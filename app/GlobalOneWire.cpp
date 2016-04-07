#include "GlobalOneWire.h"
OneWire *ow = new OneWire();
DallasTemperature *dallas = new DallasTemperature(ow);

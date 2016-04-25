#pragma once
#include "OneWireAddress.h"
#include "Temperature.h"

typedef struct {
  uint8_t version;
  OneWireAddress beer_addr;
  OneWireAddress fridge_addr;
  uint8_t heat_pin;
  uint8_t cool_pin;
  RawTemperature setpoint;
} CONTROL_SETTINGS;

extern CONTROL_SETTINGS mainSettings;

extern void init_eeprom();
extern void save_eeprom();
extern void populate_eeprom();
extern void load_from_eeprom();
extern void reset_eeprom();

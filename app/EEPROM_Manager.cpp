#include "EEPROM_Manager.h"
#include "TempControl.h"

CONTROL_SETTINGS mainSettings;
void init_eeprom() {
  EEPROM.get(0, mainSettings);
  load_from_eeprom();
}


void save_eeprom() {
  populate_eeprom();
  EEPROM.put(0, mainSettings);
}

void populate_eeprom() {
  memcpy(mainSettings.beer_addr, tempControl.beerSensor->address, 8);
  memcpy(mainSettings.fridge_addr, tempControl.fridgeSensor->address, 8);
  mainSettings.heat_pin = tempControl.heater->pinNumber();
  mainSettings.cool_pin = tempControl.chiller->pinNumber();
}

void load_from_eeprom() {
  if (mainSettings.version != 1) {
    reset_eeprom();
    return;
  }
  memcpy(tempControl.beerSensor->address, mainSettings.beer_addr, 8);
  memcpy(tempControl.fridgeSensor->address, mainSettings.fridge_addr, 8);
  if (mainSettings.heat_pin)
    tempControl.heater->setPinNumber(mainSettings.heat_pin);
  if (mainSettings.cool_pin)
    tempControl.chiller->setPinNumber(mainSettings.cool_pin);
}

void reset_eeprom() {
  memset( &mainSettings, 0, sizeof( CONTROL_SETTINGS ) );
  mainSettings.version = 1;
  mainSettings.setpoint = 2347;
  EEPROM.put(0, mainSettings);
}

#include "EEPROM_Manager.h"
#include "OutputDeviceManager.h"
#include "TempSensorManager.h"

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
  memcpy(mainSettings.beer_addr, tempSensorMgr.beerSensor.address, 8);
  memcpy(mainSettings.fridge_addr, tempSensorMgr.fridgeSensor.address, 8);
  mainSettings.heat_pin = outputDeviceMgr.heater->pinNumber();
  mainSettings.cool_pin = outputDeviceMgr.chiller->pinNumber();
}

void load_from_eeprom() {
  if (mainSettings.version != 1) {
    reset_eeprom();
    return;
  }
  memcpy(tempSensorMgr.beerSensor.address, mainSettings.beer_addr, 8);
  memcpy(tempSensorMgr.fridgeSensor.address, mainSettings.fridge_addr, 8);
  if (mainSettings.heat_pin)
    outputDeviceMgr.heater->setPinNumber(mainSettings.heat_pin);
  if (mainSettings.cool_pin)
    outputDeviceMgr.chiller->setPinNumber(mainSettings.cool_pin);
}

void reset_eeprom() {
  memset( &mainSettings, 0, sizeof( CONTROL_SETTINGS ) );
  mainSettings.version = 1;
  mainSettings.setpoint = 2347;
  EEPROM.put(0, mainSettings);
}

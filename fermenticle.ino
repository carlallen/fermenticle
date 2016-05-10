#include "OutputDeviceManager.h"
#include "TempSensorManager.h"
#include "GlobalOneWire.h"
#include "OneWireAddress.h"
#include "Temperature.h"
#include "DeviceList.h"
#include "GUI.h"
#include "TFT.h"
#include "EEPROM_Manager.h"

SYSTEM_MODE(SEMI_AUTOMATIC);
bool SYSTEM_STARTED = false;

// Loop for updating Temperature Sensors
void temperatureLoop() {
  tempSensorMgr.updateSensors();
}

Timer tempSensorTimer(1000, temperatureLoop);

void setup(void) {
  init_eeprom();
  init_tft();
  gui.splash();
  Wire.begin();
  Serial.begin(9600);
  tempSensorMgr.init();
  outputDeviceMgr.init();
  tempSensorTimer.start();
  Particle.connect();
}

void loop(void) {
  if (!SYSTEM_STARTED)
    waitFor(Particle.connected, 30000);
  SYSTEM_STARTED = true;

  gui.update();
  delay(100);
}





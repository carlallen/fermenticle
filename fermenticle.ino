#include "TempControl.h"
#include "GlobalOneWire.h"
#include "OneWireAddress.h"
#include "Temperature.h"
#include "DeviceList.h"
#include "GUI.h"
#include "TFT.h"
#include "EEPROM_Manager.h"

SYSTEM_MODE(SEMI_AUTOMATIC);
bool SYSTEM_STARTED = false;

void temperatureLoop() {
  tempControl.updateSensors();
}

Timer tempControlTimer(5000, temperatureLoop);

void setup(void) {
  init_eeprom();
  init_tft();
  gui.splash();
  Wire.begin();
  Serial.begin(9600);
  tempControl.init();
  tempControlTimer.start();
  Particle.connect();
}

void loop(void) {
  if (!SYSTEM_STARTED)
    waitFor(Particle.connected, 30000);
  SYSTEM_STARTED = true;

  gui.update();
  delay(100);
}





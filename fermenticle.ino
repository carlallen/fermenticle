#include "TempController.h"
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

void peakLoop() {
  tempController.updateFilteredTemperatures();
  tempController.detectPeaks();
  tempController.updateSettings();
}

void stateLoop() {
  tempController.updateState();
  tempController.logToSerial();
  tempController.updateOutputs();
}

void slopeLoop() {
  tempController.updateSlope();
}

Timer tempSensorTimer(5000, temperatureLoop);
Timer peakTimer(10000, peakLoop);
Timer stateTimer(1000, stateLoop);
Timer slopeTimer(60000, slopeLoop);

void setup(void) {
  init_eeprom();
  init_tft();
  gui.splash();
  Wire.begin();
  Serial.begin(9600);
  tempController.init();
  Particle.connect();
  tempSensorTimer.start();
  peakTimer.start();
  stateTimer.start();
  slopeTimer.start();
}

void loop(void) {
  if (!SYSTEM_STARTED)
    waitFor(Particle.connected, 30000);
  SYSTEM_STARTED = true;

  gui.update();
  delay(100);
}





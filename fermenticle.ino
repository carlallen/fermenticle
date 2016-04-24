#include "TempControl.h"
#include "GlobalOneWire.h"
#include "OneWireAddress.h"
#include "Temperature.h"
#include "DeviceList.h"
#include "GUI.h"
#include "TFT.h"

SYSTEM_MODE(SEMI_AUTOMATIC);
bool SYSTEM_STARTED = false;

void temperatureLoop() {
  tempControl.updateSensors();
}

Timer tempControlTimer(5000, temperatureLoop);


void setup(void) {
  init_tft();
  Wire.begin();
  Serial.begin(9600);
  tempControl.init();
  gui.splash();
  OneWireAddress addr;
  ow->reset_search();
  ow->search(addr);
  tempControl.setBeerAddress(addr);
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





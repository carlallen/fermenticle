#include "TFT.h"
#include "HomeScreen.h"
#include "TempControl.h"
#include "GlobalOneWire.h"
#include "OneWireAddress.h"
#include "Temperature.h"
#include "DeviceList.h"

Screen *main_screen;

void temperatureLoop() {
  tempControl.updateSensors();
}

Timer tempControlTimer(5000, temperatureLoop);

void setup(void) {
  main_screen = new HomeScreen();
  init_tft();
  Wire.begin();
  Serial.begin(9600);
  main_screen->update();
  tempControl.init();

  OneWireAddress addr;
  ow->reset_search();
  ow->search(addr);
  tempControl.setBeerAddress(addr);
  tempControl.init();
  tempControlTimer.start();
}

void loop(void) {
  main_screen->touch();
  main_screen->update();
  delay(100);
}





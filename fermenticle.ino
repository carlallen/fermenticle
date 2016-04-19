#include "TFT.h"
#include "HomeScreen.h"
#include "TempControl.h"
#include "GlobalOneWire.h"
#include "OneWireAddress.h"
#include "Temperature.h"

Screen *main_screen;

void tempControlLoop() {
  tempControl.updateSensors();
}

Timer tempControlTimer(5000, tempControlLoop);

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
  main_screen->update();
  // Serial.println(rawTempToFString(tempControl.beerTemp()));
  delay(1000);
}





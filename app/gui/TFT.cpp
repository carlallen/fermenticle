#include "TFT.h"
#include "application.h"
Adafruit_ILI9341 tft = Adafruit_ILI9341(D4, D5);
UTouch touchScreen = UTouch(D3, D2);
void init_tft() {
  tft.begin();
  tft.setRotation(3);
  touchScreen.InitTouch(240, 320, 2000, 210, 250, 1860, LANDSCAPE);
}

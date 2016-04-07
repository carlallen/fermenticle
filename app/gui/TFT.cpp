#include "TFT.h"
#include "application.h"
Adafruit_ILI9341 tft = Adafruit_ILI9341(D4, D5);
void init_tft() {
  tft.begin();
  tft.setRotation(3);
}

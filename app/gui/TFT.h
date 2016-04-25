#pragma once
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "UTouch.h"
extern Adafruit_ILI9341 tft;
extern void init_tft();
extern UTouch touchScreen;

#define BEER_SENSOR_COLOR ILI9341_DARKCYAN
#define FRIDGE_SENSOR_COLOR ILI9341_MAROON
#define HEATER_COLOR ILI9341_ORANGE
#define CHILLER_COLOR ILI9341_BLUE
#define WIFI_COLOR ILI9341_GREEN
#define SETTINGS_COLOR ILI9341_OLIVE
#define TEMP_PANEL_COLOR ILI9341_GREENYELLOW
#define INACTIVE_COLOR ILI9341_DARKGREY

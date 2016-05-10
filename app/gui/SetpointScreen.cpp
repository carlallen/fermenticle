#include "SetpointScreen.h"
#include "TFT.h"
#include "HomeScreen.h"
#include "EEPROM_Manager.h"

SetpointScreen::SetpointScreen() : ok_btn(110, 100, "OK"), up_button(0,3, HEATER_COLOR), down_button(1,3, CHILLER_COLOR) {
  initialized = false;
  buttons.push_back(&ok_btn);
  buttons.push_back(&up_button);
  buttons.push_back(&down_button);
}

void SetpointScreen::init() {
  tft.fillScreen(ILI9341_BLACK);
  tft.fillRect(0, 0, 320, 30, TEMP_PANEL_COLOR);
  tft.setCursor(112, 7);
  tft.setTextColor(ILI9341_WHITE, TEMP_PANEL_COLOR);
  tft.setTextSize(2);
  tft.print("Setpoint");
  tft.drawRect(0, 40, 238, 157, TEMP_PANEL_COLOR);
  initialized = true;
}

void SetpointScreen::update() {
  if (!initialized)
    init();
  ok_btn.draw();
  up_button.draw();
  down_button.draw();

  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  tft.setTextSize(6);

  String text = rawTempToFString(mainSettings.setpoint);
  tft.setCursor(10 + (5-text.length())*36, 93);
  tft.print(text);

  tft.setTextColor(ILI9341_DARKGREY, ILI9341_BLACK);
  tft.setTextSize(3);
  tft.setCursor(200,93);
  tft.print('F');
}

Screen* SetpointScreen::touch(int16_t x, int16_t y) {
  for ( auto &button : buttons ) {
    if (button->contains(x, y)) {
      button->press(true);
    } else {
      button->press(false);
    }
  }

  if (ok_btn.justReleased())
    return new HomeScreen();

  if ((up_button.isPressed() && !up_button.justPressed()) || up_button.justReleased()) {
    mainSettings.setpoint = increaseF(mainSettings.setpoint);
    if (!up_button.isPressed())
      save_eeprom();
  }
  if ((down_button.isPressed() && !down_button.justPressed()) || down_button.justReleased()) {
    mainSettings.setpoint = decreaseF(mainSettings.setpoint);
    if (!down_button.isPressed())
      save_eeprom();
  }

  return NULL;
}

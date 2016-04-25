#include "WifiScreen.h"
#include "HomeScreen.h"

WifiScreen::WifiScreen() : ok_btn(110, 100, "OK") {
  touched = false;
  initialized = false;
  update_delay = 0;
}

WifiScreen::~WifiScreen() { }

void WifiScreen::init() {
  tft.fillScreen(ILI9341_BLACK);
  tft.fillRect(0, 0, 320, 30, ILI9341_GREEN);
  tft.setCursor(75, 7);
  tft.setTextColor(ILI9341_WHITE, ILI9341_GREEN);
  tft.setTextSize(2);
  tft.print("Wi-Fi Settings");
  initialized = true;
}


void WifiScreen::update() {
  if (!initialized)
    init();
  if (update_delay == 0) {
    update_delay = 5;
    tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
    tft.setCursor(10, 45);
    tft.print("Network: ");
    tft.print(WiFi.SSID());
    tft.setCursor(10, 70);
    tft.print("IP:      ");
    tft.print(WiFi.localIP());
    tft.setCursor(10, 95);
    tft.print("Subnet:  ");
    tft.print(WiFi.subnetMask());
    tft.setCursor(10, 120);
    tft.print("Gateway: ");
    tft.print(WiFi.gatewayIP());
  } else  {
    update_delay--;
  }
  ok_btn.draw();
}


Screen* WifiScreen::touch(int16_t x, int16_t y) {
  if (ok_btn.contains(x, y)) {
    ok_btn.press(true);
  } else {
    ok_btn.press(false);
  }
  if (ok_btn.justReleased())
    return new HomeScreen();

  return NULL;
}

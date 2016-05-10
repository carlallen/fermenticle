#pragma once
#include "Touchable.h"
#include "TFT.h"
#define PANEL_BUTTON_SIZE 74

class PanelButton : public Touchable
{
public:
  PanelButton(uint8_t row, uint8_t column, int16_t color);
  PanelButton(uint8_t row, uint8_t column, int16_t color, int16_t row_offset);
  ~PanelButton() {};
  bool contains(int16_t x, int16_t y);
  void draw();
  int16_t color();
private:
  void _init(uint8_t row, uint8_t column, int16_t color, int16_t row_offset);
  int16_t _x;
  int16_t _y;
  int16_t _color;
  bool initialized;
};

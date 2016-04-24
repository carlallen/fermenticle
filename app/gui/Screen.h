#pragma once
#include "application.h"

class Screen
{
public:
  Screen() {};
  virtual ~Screen() {};
  virtual Screen* touch(int16_t x, int16_t y) = 0;
  virtual void update() = 0;
protected:
  virtual void init() = 0;
  bool initialized;
};

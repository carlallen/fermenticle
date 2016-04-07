#pragma once
#include "application.h"

class Screen
{
public:
  Screen() {};
  virtual ~Screen() {};
  virtual Screen* touch() = 0;
  virtual void update() = 0;
protected:
  virtual void init() = 0;
  bool initialized;
};

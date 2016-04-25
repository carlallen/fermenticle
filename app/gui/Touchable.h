#pragma once
#include "Screen.h"
class Touchable
{
public:
  Touchable() {
    currstate = false;
    laststate = false;
  };
  virtual ~Touchable() {};
  virtual void draw() = 0;
  virtual bool contains(int16_t x, int16_t y) = 0;
  void press(bool p) {
    laststate = currstate;
    currstate = p;
  }
  bool isPressed() { return currstate; }
  bool justPressed() { return (currstate && !laststate); }
  bool justReleased() { return (!currstate && laststate); }
protected:
  bool currstate, laststate;
};

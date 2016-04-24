#pragma once
#include "Screen.h"
class Touchable
{
public:
  Touchable() {
    currstate = false;
    laststate = false;
  };
  ~Touchable() {};
  virtual void draw();

  virtual bool contains(int16_t _x, int16_t _y);
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

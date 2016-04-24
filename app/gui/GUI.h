#pragma once
#include "Screen.h"
class GUI
{
public:
  GUI();
  ~GUI();
  void update();
  void splash();
private:
  Screen* currentScreen;
};
extern GUI gui;

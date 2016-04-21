#pragma once
#include <vector>
#include "Screen.h"
#include "HomeWidget.h"
class HomeScreen : public Screen
{
public:
  HomeScreen();
  ~HomeScreen();

  void init();
  Screen* touch();
  void update();
private:
  bool init_complete;
  HomeWidget *heat;
  HomeWidget *cool;
  HomeWidget *beerSensor;
  HomeWidget *fridgeSensor;
  HomeWidget *settings;
  HomeWidget *wifi;
  std::vector<HomeWidget*> widgets;
};

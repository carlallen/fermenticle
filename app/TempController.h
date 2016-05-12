#pragma once
#include "TempSensorManager.h"
#include "OutputDeviceManager.h"
#include "Temperature.h"

#define KpHeat 10
#define KpCool 5
#define Ki 0.02
#define KdCool -5
#define KdHeat -10

// Stay Idle when temperature is in this range
#define IDLE_RANGE_HIGH (+64)
#define IDLE_RANGE_LOW (-64)

#define HEATING_TARGET_UPPER (+32)
#define HEATING_TARGET_LOWER (-16)
#define COOLING_TARGET_UPPER (+16)
#define COOLING_TARGET_LOWER (-32)

#define COOLING_TARGET ((COOLING_TARGET_UPPER+COOLING_TARGET_LOWER)/2)
#define HEATING_TARGET ((HEATING_TARGET_UPPER+HEATING_TARGET_LOWER)/2)

// maximum history to take into account, in seconds
#define MAX_HEAT_TIME_FOR_ESTIMATE 600
#define MAX_COOL_TIME_FOR_ESTIMATE 1200

typedef enum{
  FRIDGE_CONSTANT,
  BEER_CONSTANT,
  BEER_PROFILE
} modeType;

typedef enum {
  COOLING,
  HEATING,
  IDLE,
  STARTUP,
} stateType;

class TempController
{
public:
  TempController();
  ~TempController() {} ;
  void init();
  void updateFilteredTemperatures();
  void detectPeaks();
  void updateSettings();
  void updateOutputs();
  void updateState();
  void updateSlope();
  void logToSerial();
private:
  void initFilters();
  unsigned long timeSinceHeating();
  unsigned long timeSinceCooling();
  unsigned long timeSinceIdle();
  stateType state;
  stateType previousState;
  modeType mode;
  bool doPosPeakDetect;
  bool doNegPeakDetect;

  RawTemperature fridgeTemperatureSetting;

  RawTemperature fridgeTemp[4];
  RawTemperature fridgeTempFilt[4];
  RawTemperature beerTemp[4];
  RawTemperature beerTempFilt[4];
  RawTemperature beerSlope;

  RawTemperature beerTempHistory[30];
  uint8_t beerTempHistoryIndex;

  float heatOvershootEstimator;
  float coolOvershootEstimator;
  RawTemperature fridgeSettingForNegPeakEstimate;
  RawTemperature fridgeSettingForPosPeakEstimate;
  RawTemperature posPeak;
  RawTemperature negPeak;
  float differenceIntegral;

  unsigned long lastCoolTime;
  unsigned long lastHeatTime;
  unsigned long lastIdleTime;
  float Kp;
  float Kd;
};
extern TempController tempController;

#include "TempController.h"

TempController::TempController() {
  doPosPeakDetect = false;
  doNegPeakDetect = false;
  mode = BEER_CONSTANT;
  state = STARTUP;
  previousState = IDLE;
  lastCoolTime = 0;
  lastHeatTime = 0;
  lastIdleTime = 0;
}

void TempController::init() {
  tempSensorMgr.init();
  outputDeviceMgr.init();
}

void TempController::initFilters() {
  RawTemperature currentBeerTemp = tempSensorMgr.beerTemp();
  RawTemperature currentFridgeTemp = tempSensorMgr.fridgeTemp();
  for(int i=0; i<4 ;i++) {
    fridgeTemp[i] = currentFridgeTemp;
    fridgeTempFilt[i] = currentFridgeTemp;
    beerTemp[i] = currentBeerTemp;
    beerTempFilt[i] = currentBeerTemp;
  }

  for(int i=0; i<30; i++) {
    beerTempHistory[i] = beerTempFilt[3];
  }
  beerSlope = 0;
  beerTempHistoryIndex = 0;
}

void TempController::updateFilteredTemperatures() {
// Input for filter
  fridgeTemp[0] = fridgeTemp[1]; fridgeTemp[1] = fridgeTemp[2]; fridgeTemp[2] = fridgeTemp[3];
  fridgeTemp[3] = tempSensorMgr.fridgeTemp();

  // Butterworth filter with cutoff frequency 0.01*sample frequency (FS=0.1Hz)
  fridgeTempFilt[0] = fridgeTempFilt[1]; fridgeTempFilt[1] = fridgeTempFilt[2]; fridgeTempFilt[2] = fridgeTempFilt[3];
  // fridgeTempFilt[3] =   (fridgeTemp[0] + fridgeTemp[3] + 3 * (fridgeTemp[1] + fridgeTemp[2]))/3.430944333e+04
  //             + ( 0.8818931306    * fridgeTempFilt[0]) + (  -2.7564831952     * fridgeTempFilt[1]) + ( 2.8743568927 * fridgeTempFilt[2] );
  // Moving average filter
  fridgeTempFilt[3] = (fridgeTemp[0] + fridgeTemp[1] + fridgeTemp[2] + fridgeTemp[3])/4;

  beerTemp[0] = beerTemp[1]; beerTemp[1] = beerTemp[2]; beerTemp[2] = beerTemp[3];
  beerTemp[3] = tempSensorMgr.beerTemp();

   // Butterworth filter with cutoff frequency 0.01*sample frequency (FS=0.1Hz)
  beerTempFilt[0] = beerTempFilt[1]; beerTempFilt[1] = beerTempFilt[2]; beerTempFilt[2] = beerTempFilt[3];
  // beerTempFilt[3] =   (beerTemp[0] + beerTemp[3] + 3 * (beerTemp[1] + beerTemp[2]))/3.430944333e+04
  //             + ( 0.8818931306    * beerTempFilt[0]) + (  -2.7564831952     * beerTempFilt[1]) + ( 2.8743568927 * beerTempFilt[2] );
  // Moving average filter
  beerTempFilt[3] = (beerTemp[0] + beerTemp[1] + beerTemp[2] + beerTemp[3])/4;
}

void TempController::detectPeaks(void){
  //detect peaks in fridge temperature to tune overshoot estimators
  if(doPosPeakDetect && state!=HEATING){
    if(fridgeTempFilt[3] <= fridgeTempFilt[2] && fridgeTempFilt[2] >= fridgeTempFilt[1]){ // maximum
      posPeak=fridgeTempFilt[2];
      if(posPeak>fridgeSettingForPosPeakEstimate+HEATING_TARGET_UPPER){
        //should not happen, estimated overshoot was too low, so adjust overshoot estimator
        heatOvershootEstimator=heatOvershootEstimator*(1.2+min((posPeak-(fridgeSettingForPosPeakEstimate+HEATING_TARGET_UPPER))*.03,0.3));
        //TODO: saveSettings();
      }
      if(posPeak<fridgeSettingForPosPeakEstimate+HEATING_TARGET_LOWER){
        //should not happen, estimated overshoot was too high, so adjust overshoot estimator
        heatOvershootEstimator=heatOvershootEstimator*(0.8+max((posPeak-(fridgeSettingForPosPeakEstimate+HEATING_TARGET_LOWER))*.03,-0.3));
        //TODO: saveSettings();
      }
      doPosPeakDetect=0;
    }
    else if(timeSinceHeating() > 580000UL && timeSinceCooling() > 900000UL && fridgeTempFilt[3] < fridgeSettingForPosPeakEstimate+HEATING_TARGET_LOWER){
      //there was no peak, but the estimator is too low. This is the heat, then drift up situation.
        posPeak=fridgeTempFilt[3];
        heatOvershootEstimator=heatOvershootEstimator*(0.8+max((posPeak-(fridgeSettingForPosPeakEstimate+HEATING_TARGET_LOWER))*.03,-0.3));
        //TODO: saveSettings();
        doPosPeakDetect=0;
    }
  }
  if(doNegPeakDetect && state!=COOLING){
    if(fridgeTempFilt[3] >= fridgeTempFilt[2] && fridgeTempFilt[2] <= fridgeTempFilt[1]){ // minimum
      negPeak=fridgeTempFilt[2];
      if(negPeak<fridgeSettingForNegPeakEstimate+COOLING_TARGET_LOWER){
        //should not happen, estimated overshoot was too low, so adjust overshoot estimator
        coolOvershootEstimator=coolOvershootEstimator*(1.2+min(((fridgeSettingForNegPeakEstimate+COOLING_TARGET_LOWER)-negPeak)*.03,0.3));
        //TODO: saveSettings();
      }
      if(negPeak>fridgeSettingForNegPeakEstimate+COOLING_TARGET_UPPER){
        //should not happen, estimated overshoot was too high, so adjust overshoot estimator
        coolOvershootEstimator=coolOvershootEstimator*(0.8+max(((fridgeSettingForNegPeakEstimate+COOLING_TARGET_UPPER)-negPeak)*.03,-0.3));
        //TODO: saveSettings();
      }
      doNegPeakDetect=0;
    }
    else if(timeSinceCooling() > 1780000UL && timeSinceHeating() > 1800000UL && fridgeTempFilt[3] > fridgeSettingForNegPeakEstimate+COOLING_TARGET_UPPER){
      //there was no peak, but the estimator is too low. This is the cool, then drift down situation.
        negPeak=fridgeTempFilt[3];
        coolOvershootEstimator=coolOvershootEstimator*(0.8+max((negPeak-(fridgeSettingForNegPeakEstimate+COOLING_TARGET_UPPER))*.03,-0.3));
        //TODO: saveSettings();
        doNegPeakDetect=0;
    }
  }
}

void TempController::updateSettings() {
  if(mode == BEER_CONSTANT || mode == BEER_PROFILE && state != STARTUP){
    RawTemperature beerTemperatureDifference =  mainSettings.setpoint-beerTempFilt[3];
    if(abs(beerTemperatureDifference) < 5 && ((beerSlope <= 0.7 && beerSlope >= 0) || (beerSlope >= -1.4 && beerSlope <= 0))){     //difference is smaller than .5 degree and slope is almost horizontal
      if(abs(beerTemperatureDifference)> 0.5){
        differenceIntegral = differenceIntegral + beerTemperatureDifference;
      }
    }
    else{
      differenceIntegral = differenceIntegral*0.9;
    }

    if(beerTemperatureDifference<0){ //linearly go to cool parameters in 3 hours
      Kp = constrain(Kp+(KpCool-KpHeat)/(360*3), KpCool, KpHeat);
      Kd = constrain(Kd+(KdCool-KdHeat)/(360*3), KdHeat, KdCool);
    }
    else{ //linearly go to heat parameters in 3 hours
      Kp = constrain(Kp+(KpHeat-KpCool)/(360*3), KpCool, KpHeat);
      Kd = constrain(Kd+(KdHeat-KdCool)/(360*3), KdHeat, KdCool);
    }
    fridgeTemperatureSetting = constrain(mainSettings.setpoint + Kp* beerTemperatureDifference + Ki* differenceIntegral + Kd*beerSlope, 512, 11520);
  }
}

void TempController::updateOutputs(){
  switch (state){
  case IDLE:
  case STARTUP:
    outputDeviceMgr.idle();
    break;
  case COOLING:
    outputDeviceMgr.cool();
    break;
  case HEATING:
    outputDeviceMgr.heat();
    break;
  default:
    outputDeviceMgr.idle();
    break;
  }
}

void TempController::updateState(void){
  RawTemperature estimatedOvershoot;
  RawTemperature estimatedPeakTemperature;
  //update state
  switch(state){
    case STARTUP:
      if (tempSensorMgr.ready()) {
        initFilters();
        fridgeTemperatureSetting = mainSettings.setpoint;
        state = IDLE;
      } else {
        return;
      }
    case IDLE:
      lastIdleTime=millis();
      if(((timeSinceCooling() > 900000UL || doNegPeakDetect==0) && (timeSinceHeating()>600000UL || doPosPeakDetect==0)) || state==STARTUP){ //if cooling is 15 min ago and heating 10
        if(fridgeTempFilt[3]> fridgeTemperatureSetting+IDLE_RANGE_HIGH){
          if(mode!=FRIDGE_CONSTANT){
            if(beerTempFilt[3]>mainSettings.setpoint+6){ // only start cooling when beer is too warm (0.05 degree idle space)
              state=COOLING;
            }
          } else {
            state=COOLING;
          }
          return;
        }
        if(fridgeTempFilt[3]< fridgeTemperatureSetting+IDLE_RANGE_LOW){
          if(mode!=FRIDGE_CONSTANT){
            if(beerTempFilt[3]<mainSettings.setpoint-6){ // only start heating when beer is too cold (0.05 degree idle space)
              state=HEATING;
            }
          }
          else{
            state=HEATING;
          }
          return;
        }
      }
      if(timeSinceCooling()>1800000UL){ //30 minutes
        doNegPeakDetect=0;  //peak would be from drifting in idle, not from cooling
      }
      if(timeSinceHeating()>900000UL){ //20 minutes
        doPosPeakDetect=0;  //peak would be from drifting in idle, not from heating
      }
      break;
    case COOLING:
      doNegPeakDetect=1;
      lastCoolTime = millis();
      estimatedOvershoot = coolOvershootEstimator  * min(MAX_COOL_TIME_FOR_ESTIMATE, (float) timeSinceIdle()/(1000))/60;
      estimatedPeakTemperature = fridgeTempFilt[3] - estimatedOvershoot;
      if(estimatedPeakTemperature <= fridgeTemperatureSetting + COOLING_TARGET){
        fridgeSettingForNegPeakEstimate=fridgeTemperatureSetting;
        state=IDLE;
        return;
      }
      break;
    case HEATING:
       lastHeatTime=millis();
       doPosPeakDetect=1;
       estimatedOvershoot = heatOvershootEstimator * min(MAX_HEAT_TIME_FOR_ESTIMATE, (float) timeSinceIdle()/(1000))/60;
       estimatedPeakTemperature = fridgeTempFilt[3] + estimatedOvershoot;
      if(estimatedPeakTemperature >= fridgeTemperatureSetting + HEATING_TARGET){
        fridgeSettingForPosPeakEstimate=fridgeTemperatureSetting;
        state=IDLE;
        return;
      }
      break;
    default:
      state = IDLE; //go to idle, should never happen
  }
}

void TempController::updateSlope() { //called every minute
  beerTempHistory[beerTempHistoryIndex]=beerTempFilt[3];
  beerSlope = beerTempHistory[beerTempHistoryIndex]-beerTempHistory[(beerTempHistoryIndex+1)%30];
  beerTempHistoryIndex = (beerTempHistoryIndex+1)%30;
}

void TempController::logToSerial() {
  Serial.print("Beer Temp: ");
  Serial.println(rawTempToFString(beerTempFilt[3]));

  Serial.print("Fridge Temp: ");
  Serial.println(rawTempToFString(fridgeTempFilt[3]));

  Serial.print("Beer Setpoint: ");
  Serial.println(rawTempToFString(mainSettings.setpoint));

  Serial.print("Fridge Setpoint: ");
  Serial.println(rawTempToFString(fridgeTemperatureSetting));

  Serial.print("State: ");
  switch(state) {
    case STARTUP:
      Serial.println("STARTUP");
      break;
    case IDLE:
      Serial.println("IDLE");
      break;
    case HEATING:
      Serial.println("HEATING");
      break;
    case COOLING:
      Serial.println("COOLING");
      break;
  }

}


unsigned long TempController::timeSinceHeating() {
  unsigned long currentTime = millis();
  unsigned long timeSinceLastOn;
  if(currentTime>=lastHeatTime){
    timeSinceLastOn = currentTime - lastHeatTime;
  }
  else{
    // millis() overflow has occured
    timeSinceLastOn = (currentTime + 1440000) - (lastHeatTime +1440000); // add a day to both for calculation
  }
  return timeSinceLastOn;
}

unsigned long TempController::timeSinceCooling() {
  unsigned long currentTime = millis();
  unsigned long timeSinceLastOn;
  if(currentTime>=lastCoolTime){
    timeSinceLastOn = currentTime - lastCoolTime;
  }
  else{
    // millis() overflow has occured
    timeSinceLastOn = (currentTime + 1440000) - (lastCoolTime +1440000); // add a day to both for calculation
  }
  return timeSinceLastOn;
}

unsigned long TempController::timeSinceIdle(){
  unsigned long currentTime = millis();
  unsigned long timeSinceLastOn;
  if(currentTime>=lastIdleTime){
    timeSinceLastOn = currentTime - lastIdleTime;
  }
  else{
    // millis() overflow has occured
    timeSinceLastOn = (currentTime + 1440000) - (lastIdleTime +1440000); // add a day to both for calculation
  }
  return timeSinceLastOn;
}

TempController tempController;

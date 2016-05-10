#pragma once
#include "DallasTemperature.h"
#include "application.h"

typedef int16_t RawTemperature;

static String disconnectedString() {
  return "--.-";
}

static String printedNumber(RawTemperature number) {
  String value;
  value.reserve(5);
  value.concat(number/10);
  value.concat('.');
  value.concat(abs(number)%10);
  return value;
}

static RawTemperature rawToFVal(RawTemperature raw) {
  return raw*18/128+320;
}

static RawTemperature rawToCVal(RawTemperature raw) {
  return raw*10/128;
}

static RawTemperature fValToRaw(RawTemperature fVal) {
  //add 5 hundreds of a degree before converting to compensate for error
  return ((fVal-320)*10+5)*128/180;
}

static RawTemperature cValToRaw(RawTemperature cVal) {
  return cVal*128/10;
}

static RawTemperature increaseF(RawTemperature raw) {
  return fValToRaw(rawToFVal(raw) + 1);
}

static RawTemperature decreaseF(RawTemperature raw) {
  return fValToRaw(rawToFVal(raw) - 1);
}

static RawTemperature increaseC(RawTemperature raw) {
  return cValToRaw(rawToCVal(raw) + 1);
}

static RawTemperature decreaseC(RawTemperature raw) {
  return cValToRaw(rawToCVal(raw) - 1);
}

static String rawTempToFString(RawTemperature raw) {
  if (raw == DEVICE_DISCONNECTED_RAW) {
    return disconnectedString();
  } else {
    return printedNumber(rawToFVal(raw));
  }
}

static String rawTempToCString(RawTemperature raw) {
  if (raw == DEVICE_DISCONNECTED_RAW) {
    return disconnectedString();
  } else {
    return printedNumber(rawToCVal(raw));
  }
}


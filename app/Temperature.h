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

static String rawTempToFString(RawTemperature raw) {
  if (raw == DEVICE_DISCONNECTED_RAW) {
    return disconnectedString();
  } else {
    return printedNumber(raw*18/128+320);
  }
}

static String rawTempToCString(RawTemperature raw) {
  if (raw == DEVICE_DISCONNECTED_RAW) {
    return disconnectedString();
  } else {
    return printedNumber(raw*10/128);
  }
}


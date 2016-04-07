#pragma once
#include "DallasTemperature.h"
#include "application.h"

static String disconnectedString() {
  return " --.-";
}

static String printedNumber(int16_t number) {
  String numberString = String(number);
  String value;
  uint8_t length = numberString.length();
  if (number < 0 && number > -9)
    value = String(" -0. ");
  else
    value = String("  0. ");

  value.setCharAt(4, numberString.charAt(length-1));
  if (length > 1 && numberString.charAt(length-2) != '-')
    value.setCharAt(2, numberString.charAt(length-2));
  if (length > 2)
    value.setCharAt(1, numberString.charAt(length-3));
  if (length > 3)
    value.setCharAt(0, numberString.charAt(length-4));
  return value;
}

static String rawTempToFString(int16_t raw) {
  if (raw == DEVICE_DISCONNECTED_RAW) {
    return disconnectedString();
  } else {
    return printedNumber(raw*18/128+320);
  }
}

static String rawTempToCString(int16_t raw) {
  if (raw == DEVICE_DISCONNECTED_RAW) {
    return disconnectedString();
  } else {
    return printedNumber(raw*10/128);
  }
}


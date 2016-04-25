#pragma once
#include "application.h"
typedef uint8_t OneWireAddress[8];

static uint8_t fromHex(char c){
  return (c >= 'A') ? c - 'A' + 10 : c - '0';
}

static char toHex(uint8_t b){
  return ((b > 9) ? b - 10 + 'A' : b + '0');
}

static String addressToString(OneWireAddress address) {
  String addressString = "";
  addressString.reserve(16);
  for (int i = 0; i < 8; i++) {
    uint8_t b = (address[i] >> 4) & 0x0f;
    addressString += toHex(b);
    b      = address[i] & 0x0f;
    addressString += toHex(b);
  }
  return addressString;
}

static bool addressesMatch(OneWireAddress address1, OneWireAddress address2) {
  for(int i = 0; i < 8; i++) {
    if (address1[i] != address2[i])
      return false;
  }
  return true;
}

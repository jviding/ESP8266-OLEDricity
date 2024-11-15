#pragma once

#include <Arduino.h>
#include "eeprom_ctrl/eeprom_test.h"

//#include "../../../../networking/wifi_ctrl/eeprom_ctrl/eeprom_ctrl.h"


class WiFi_test {
public:
  static void test_eeprom();

private:
  static bool some();
};
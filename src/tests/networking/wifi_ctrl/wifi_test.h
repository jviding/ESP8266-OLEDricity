#pragma once

#include <Arduino.h>
#include "../../../networking/wifi_ctrl/wifi_ctrl.h"

#include "eeprom_ctrl/eeprom_test.h"
#include "server_ctrl/server_test.h"


class WiFi_test {
public:
  static bool test_wifi_modes();
  static bool test_eeprom();
  static bool test_server_over_WiFi();
  static bool test_server_over_HotSpot();

private:
  static bool toggle_wifi();
  static bool toggle_hotspot();
};

#pragma once

#include <Arduino.h>
#include "../../../../networking/wifi_ctrl/eeprom_ctrl/eeprom_ctrl.h"


class Eeprom_test {
public:
  static void test();

private:
  static bool try_read();
  static bool try_write();
  static bool print_result(bool res_ok, int num_test);
};
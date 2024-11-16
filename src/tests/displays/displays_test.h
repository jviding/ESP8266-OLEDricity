#pragma once

#include <Arduino.h>
#include "../../displays/displays.h"
#include "../../networking/networking.h"

class Displays_test {
public:
  static void test_displays_with_data_fast_loop();
  static bool enable_networking_for_real_data();
};

#pragma once

#include <Arduino.h>
#include "../../displays/displays.h"
#include "../../networking/networking.h"

#include "chart/chart_test.h"
#include "leds/leds_test.h"


class Displays_test {
public:
  static void test_displays_with_data_fast_loop();
  static bool enable_networking_for_real_data();

  // CHART
  static void test_chart_write_hotspot_ip_and_pwd();

  // LEDS
  static void test_leds_rgb();
};

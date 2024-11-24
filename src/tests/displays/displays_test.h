#pragma once

#include <Arduino.h>
#include "../../displays/displays.h"

#include "chart/chart_test.h"
#include "leds/leds_test.h"


class Displays_test {
public:
  // Functions
  static void test_data_fast_loop(price_data_t* data, int time_now);

  // CHART
  static void test_chart_hotspot_message();

  // LEDS
  static void test_leds_rgb();
};

#pragma once

#include <Arduino.h>
#include "../displays/displays.h"
#include "../leds/leds.h"
#include "../networking/networking.h"
#include "networking/network_test.h"
#include "displays/displays_test.h"
#include "leds/leds_test.h"


class Tests {
public:
  static void test();
  static void debug_print_heap();

private:
  static void test_displays();
  static void test_leds();
  static void test_networking();
};

#pragma once

#include <Arduino.h>
#include "../displays/displays.h"
#include "../networking/networking.h"
#include "networking/network_test.h"
#include "displays/displays_test.h"


class Tests {
public:
  static void test();
  static void debug_print_heap();

private:
  static void test_displays();
  static void test_networking();
};

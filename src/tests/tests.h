#pragma once

#include <Arduino.h>
#include "../networking/networking.h"
#include "networking/network_test.h"


class Tests {
public:
  static void test();
  static void debug_print_heap();

private:
  static void test_networking();
};

#pragma once

#include <Arduino.h>
#include "../displays/dataset.h"


class Tests {
public:
  static void debug_print_heap();
  static void print_time(int time_now);
  static void print_price_data(price_data_t* data);
};
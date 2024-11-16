#pragma once

#include <Arduino.h>
#include "../../../networking/https_req/https_req.h"


class HTTPS_test {
public:
  static void get_and_print_price_data();
};
#pragma once

#include <Arduino.h>
#include "../../../networking/ntp_time/ntp_time.h"


class NTP_test {
public:
  static void get_and_print_time();
};
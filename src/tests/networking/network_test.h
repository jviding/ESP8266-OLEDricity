#pragma once

#include <Arduino.h>
#include "../../networking/networking.h"

#include "https_test/https_test.h"
#include "ntp_test/ntp_test.h"
#include "wifi_ctrl/wifi_test.h"


class Network_test {
public:

  static bool test_WiFi_reset();
  static bool test_WiFi_reset_then_join();

  // HTTPS
  static void test_get_and_print_price_data();
  // NTP
  static void test_get_and_print_time();
  // WIFI
  static bool test_wifi_modes();
  static bool test_wifi_eeprom();
  static bool test_wifi_server_over_WiFi();
  static bool test_wifi_server_over_HotSpot();

private:
  static bool toggle_WiFi();
};

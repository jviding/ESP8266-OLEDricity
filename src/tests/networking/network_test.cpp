#include "network_test.h"


void Network_test::test_get_and_print_price_data() {
  Networking::connect();
  return HTTPS_test::get_and_print_price_data();
};

void Network_test::get_and_print_time() {
  Networking::connect();
  return NTP_test::get_and_print_time();
};

bool Network_test::test_wifi_modes() {
  return WiFi_test::test_wifi_modes();
};

bool Network_test::test_wifi_eeprom() {
  return WiFi_test::test_eeprom();
};

bool Network_test::test_wifi_server_over_WiFi() {
  return WiFi_test::test_server_over_WiFi();
};

bool Network_test::test_wifi_server_over_HotSpot() {
  return WiFi_test::test_server_over_HotSpot();
};

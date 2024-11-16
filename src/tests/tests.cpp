#include "tests.h"


void Tests::test() {
  test_networking();
};

void Tests::test_networking() {
  Networking::enable();
  while (true) {
    // HTTPS
    //Network_test::test_get_and_print_price_data();
    // NTP
    //Network_test::get_and_print_time();
    // WIFI
    //Network_test::test_wifi_modes();
    //Network_test::test_wifi_eeprom();
    //Network_test::test_wifi_server_over_WiFi();
    Network_test::test_wifi_server_over_HotSpot();
    // Memory check
    debug_print_heap();
    delay(3000);
  }
};

void Tests::debug_print_heap() {
  uint32_t heap = ESP.getFreeHeap();
  Serial.println("\n");
  Serial.print("Free heap: "); Serial.println(heap);
  Serial.println("\n");
};

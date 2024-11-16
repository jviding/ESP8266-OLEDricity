#include "tests.h"


void Tests::test() {
  test_displays();
  //test_leds();
  //test_networking();
};

void Tests::test_displays() {
  Displays::init();
  Displays_test::enable_networking_for_real_data();
  while (true) {
    // Test Displays (requires enable_networking_for_real_data)
    Displays_test::test_displays_with_data_fast_loop();
    /*
      MEMORY CHECK
    */
    debug_print_heap();
    delay(3000);
  }
};

void Tests::test_leds() {
  Leds::init();
  while (true) {

    /*
      MEMORY CHECK
    */
    debug_print_heap();
    delay(3000);
  }
};

void Tests::test_networking() {
  Networking::enable();
  while (true) {
    // Reset sequence
    Network_test::test_WiFi_reset_sequence();
    // HTTPS
    //Network_test::test_get_and_print_price_data();
    // NTP
    //Network_test::test_get_and_print_time();
    // WIFI
    //Network_test::test_wifi_modes();
    //Network_test::test_wifi_eeprom();
    //Network_test::test_wifi_server_over_WiFi();
    //Network_test::test_wifi_server_over_HotSpot();
    /*
      MEMORY CHECK
    */
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

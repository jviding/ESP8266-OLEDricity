#include "tests.h"


void Tests::test() {
  //test_displays();
  //test_networking();
  test_both();
};


void Tests::test_displays() {
  Displays::init();
  while (true) {
    // CHART
    //Displays_test::test_chart_write_hotspot_ip_and_pwd();
    // LEDS
    Displays_test::test_leds_rgb();
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
    Network_test::test_WiFi_reset_then_join();
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



void Tests::test_both() {
  // Enable
  Displays::init();
  if (!Networking::enable()) {
    Network_test::test_WiFi_reset();
  }
  // Run tests
  while (true) {
    bool res_ok = true;
    Serial.println("## Tests: Try get time and data");
    // Get time
    int time_now = 0;
    res_ok = res_ok && Networking::get_time(&time_now);
    // Get data
    price_data_t* data = nullptr;
    res_ok = res_ok && Networking::get_data(&data);
    // Fast loop
    while (res_ok) {
      Displays_test::test_data_fast_loop(data, time_now);
      delay(1000);
    }
    // Release
    while (data != nullptr) {
      price_data_t* temp = data->next;
      delete data;
      data = temp; 
    }
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



#include "displays_test.h"


void Displays_test::test_data_fast_loop(price_data_t* data, int time_now) {
  while (true) {
    // Loop until end of data
    if (Displays::draw(data, time_now) == 0) {
      break;
    }
    // +1 hour
    if (time_now % 100 == 23) {
      time_now += 100 - 23;
    } else {
      time_now++;
    }
    delay(500);
  }
};

void Displays_test::test_chart_write_hotspot_ip_and_pwd() {
  Chart_test::test_write_hotspot_ip_and_pwd();
};

void Displays_test::test_leds_rgb() {
  Leds_test::test_rgb();
};

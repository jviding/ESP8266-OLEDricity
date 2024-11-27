#include "ntp_test.h"


void NTP_test::get_and_print_time() {
  int time_now = 0;
  NTP_time::get_finnish_time_as_data_time(&time_now);
  Serial.println("\n");
  Serial.print("Time now: "); Serial.println(time_now);
  Serial.println("\n");
  delay(2000);
};

void NTP_test::test_wait_until_hour_changed() {
  int time_now = 0;
  while (true) {
    NTP_time::get_finnish_time_as_data_time(&time_now);
    NTP_time::wait_until_hour_changed(time_now);
    Serial.println("## NTP test wait: Hour changed!");
  }
};

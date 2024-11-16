#include "ntp_test.h"


void NTP_test::get_and_print_time() {
  int time_now = 0;
  NTP_time::get_finnish_time(&time_now);
  Serial.println("\n");
  Serial.print("Time now: "); Serial.println(time_now);
  Serial.println("\n");
  delay(2000);
};

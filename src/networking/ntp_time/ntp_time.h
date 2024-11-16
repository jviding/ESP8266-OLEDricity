#pragma once

#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Timezone.h>

#include "../../config.h"
#define NTP_SRC   CONFIG_NTP_SRC


// Get Finnish time from external source.
// Returned as integer, in format YYYYmmDDhh.

class NTP_time {
public:
  // Functions
  static bool enable();
  static bool get_finnish_time(int* time_now);

private:
  // Variables
  static WiFiUDP udp;
  static NTPClient ntpClient;
  static unsigned long lastNtpTime;
  static unsigned long lastMillis;

  // Functions
  static bool update_NTP_time();
  static int to_data_time(time_t time);
};
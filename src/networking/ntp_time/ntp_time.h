#pragma once

#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Timezone.h>

#include "../../config.h"
#define NTP_SRC   CONFIG_NTP_SRC


// Get Finnish time from external source.

class NTP_time {
public:
  // Functions
  static bool enable();
  static bool get_finnish_time(time_t* time);

private:
  // Variables
  static WiFiUDP udp;
  static NTPClient ntpClient;
};
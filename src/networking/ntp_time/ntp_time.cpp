#include "ntp_time.h"


WiFiUDP NTP_time::udp;
NTPClient NTP_time::ntpClient(udp, NTP_SRC);

TimeChangeRule finnish_summer_time_start = { "EEST", Last, Sun, Mar, 2, 3*60 };   // EEST +3h
TimeChangeRule finnish_winter_time_start = { "EET",  Last, Sun, Oct, 3, 2*60 };   // EET  +2h
Timezone finnish_timezone(finnish_summer_time_start, finnish_winter_time_start);


bool NTP_time::enable() {
  if (udp.begin(123) == 0) {
    Serial.println("NTP: Failed enabling.");
    return false;
  } else {   
    Serial.println("NTP: Enabled.");
    ntpClient.begin();
    return true;
  }
};

bool NTP_time::get_finnish_time(time_t* time) {
  Serial.print("NTP: Getting time...");
  // Get time
  if (!ntpClient.update()) {
    Serial.println("Failed.");
    return false;
  }
  // Done
  Serial.println("OK.");
  *time = ntpClient.getEpochTime();
  *time = finnish_timezone.toLocal(*time);
  return true;
};

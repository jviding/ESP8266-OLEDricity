#include "networking.h"


WiFiUDP Networking::udp;
NTPClient Networking::ntpClient(udp, NTP_SRC);

TimeChangeRule finnish_summer_time_start = { "EEST", Last, Sun, Mar, 2, 3*60 }; // EEST +3h
TimeChangeRule finnish_winter_time_start = { "EET",  Last, Sun, Oct, 3, 2*60 };  // EET  +2h
Timezone finnish_timezone(finnish_summer_time_start, finnish_winter_time_start);


void Networking::ntp_enable() {
  udp.begin(123);
  ntpClient.begin();
  Serial.println("Enabled NTP.");
};

time_t Networking::ntp_get_epoch_time() {
  Serial.print("Get time from NTP...");
  // Get time
  ntpClient.update();
  time_t epoch = ntpClient.getEpochTime();
  time_t local_time = finnish_timezone.toLocal(epoch);
  // Done
  Serial.println("OK.");
  return local_time;
};

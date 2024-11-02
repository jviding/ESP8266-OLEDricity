#include "ntp_time.h"


WiFiUDP NTP_time::udp;
NTPClient NTP_time::ntpClient(udp, NTP_SRC);

TimeChangeRule finnish_summer_time_start = { "EEST", Last, Sun, Mar, 2, 3*60 };   // EEST +3h
TimeChangeRule finnish_winter_time_start = { "EET",  Last, Sun, Oct, 3, 2*60 };   // EET  +2h
Timezone finnish_timezone(finnish_summer_time_start, finnish_winter_time_start);

unsigned long lastNtpTime = 0;
unsigned long lastMillis = 0;


bool NTP_time::enable() {
  if (udp.begin(123) == 0) {
    Serial.println("NTP: Failed enabling.");
    return false;
  }  
  Serial.println("NTP: Enabled.");
  ntpClient.begin();
  delay(200);
  return update();
};

bool NTP_time::update() {
  Serial.print("NTP: Updating time from server...");
  if (!ntpClient.update()) {
    Serial.println("Failed.");
    return false;
  }
  Serial.println("Ok.");
  lastNtpTime = ntpClient.getEpochTime();
  lastMillis = millis();
  return true;
};

int NTP_time::to_data_time(time_t time_now) {
  int time = 0;                         // ----------
  time += year(time_now)  *100*100*100; // YYYY------
  time += month(time_now) *100*100;     // ----MM----
  time += day(time_now)   *100;         // ------DD--
  time += hour(time_now);               // --------HH
  return time;                          // YYYYMMDDHH
};

bool NTP_time::get_finnish_time(int* time) {
  unsigned long elapsedTime = (millis() - lastMillis) / 1000;
  int oneDay = 24 * 60 * 60; // h * min * s
  if (elapsedTime < oneDay) {
    Serial.println("NTP: Using system local time.");
  } else if (!update()) {
    return false;
  }
  time_t time_now = finnish_timezone.toLocal(lastNtpTime + elapsedTime);
  *time = to_data_time(time_now);
  return true;
};

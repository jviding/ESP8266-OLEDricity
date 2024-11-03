#include "ntp_time.h"


WiFiUDP NTP_time::udp;
NTPClient NTP_time::ntpClient(udp, NTP_SRC);

TimeChangeRule finnish_summer_time_start = { "EEST", Last, Sun, Mar, 2, 3*60 };   // EEST +3h
TimeChangeRule finnish_winter_time_start = { "EET",  Last, Sun, Oct, 3, 2*60 };   // EET  +2h
Timezone finnish_timezone(finnish_summer_time_start, finnish_winter_time_start);

unsigned long NTP_time::lastNtpTime = 0;
unsigned long NTP_time::lastMillis = 0;


bool NTP_time::enable() {
  if (udp.begin(123) == 0) {
    Serial.println("NTP: Failed enabling.");
    return false;
  }  
  Serial.println("NTP: Enabled.");
  ntpClient.begin();
  delay(200);
  return get_NTP_time();
};

bool NTP_time::get_NTP_time() {
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

int NTP_time::to_data_time(time_t time) {
  int data_time = 0;                     // ----------
  data_time += year(time)  *100*100*100; // YYYY------
  data_time += month(time) *100*100;     // ----MM----
  data_time += day(time)   *100;         // ------DD--
  data_time += hour(time);               // --------HH
  return data_time;                      // YYYYMMDDHH
};

bool NTP_time::get_finnish_time(int* time_now) {
  unsigned long elapsedTime = (millis() - lastMillis) / 1000;
  unsigned long oneDay = 24 * 60 * 60; // h * min * s
  if (elapsedTime < oneDay) {
    Serial.println("NTP: Using local system time.");
  } else if (!get_NTP_time()) {
    return false;
  }
  time_t time = finnish_timezone.toLocal(lastNtpTime + elapsedTime);
  *time_now = to_data_time(time);
  return true;
};

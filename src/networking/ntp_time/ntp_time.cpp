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
  return true;
};

bool NTP_time::update_NTP_time() {
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

bool NTP_time::get_finnish_time(time_t* time) {
  unsigned long elapsedTime = (millis() - lastMillis) / 1000;
  unsigned long oneDay = 24 * 60 * 60; // h * min * s
  if (lastNtpTime != 0 && elapsedTime < oneDay) {
    Serial.println("NTP: Using local system time.");
  } else if (!update_NTP_time()) {
    return false;
  }
  *time = finnish_timezone.toLocal(lastNtpTime + elapsedTime);
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

bool NTP_time::get_finnish_time_as_data_time(int* time_now) {
  time_t time = 0;
  if (get_finnish_time(&time)) {
    *time_now = to_data_time(time);
    return true;
  }
  return false;
};

bool NTP_time::wait_until_hour_changed(int time_now) {

  int minutes = 0;

  while (true) {
    // Get new time
    time_t time_new = 0;
    if (!get_finnish_time(&time_new)) return false;
    // Check if hour changed
    if (hour(time_new) != time_now % 100) return true;
    
    // TEST
    if (minute(time_new) != minutes) {
      minutes = minute(time_new);
      Serial.print("NTP: MINUTE CHANGED TO ");
      Serial.println(minutes);
    }
    
    // If not, wait...
    int wait_time = 0;
    //wait_time += (59 - minute(time_new)) * 60; // Add minutes as seconds
    wait_time += (59 - second(time_new));      // Add seconds
    // ...for at least 3 seconds.
    if (wait_time < 3) wait_time = 3;
    // Wait
    delay(wait_time * 1000);

  }
};

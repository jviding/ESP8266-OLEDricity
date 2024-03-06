#include "networking.h"


WiFiUDP Networking::udp;
NTPClient Networking::ntpClient(udp, NTP_SRC);

void Networking::ntp_enable() {
  udp.begin(123);
  ntpClient.begin();
  ntpClient.setTimeOffset(NTP_ZONE);
  Serial.println("Enabled NTP.");
};

uint32_t Networking::ntp_get_epoch_time() {
  Serial.print("Get time from NTP...");
  // Get time
  ntpClient.update();
  time_t epoch = ntpClient.getEpochTime();
  // Done
  Serial.println("OK.");
  return epoch;
};

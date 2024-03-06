#include "networking.h"


WiFiUDP Networking::udp;


void Networking::ntp_enable() {
  udp.begin(123);
  Serial.println("Enabled NTP.");
};

bool Networking::ntp_wait_response() {
  for (size_t i = 0; i < NTP_TIMEOUT; i++) {
    delay(1000);
    if (udp.parsePacket()) {
      return true;
    }
  }
  return false;
};

uint32_t Networking::ntp_get_epoch_time() {
  Serial.print("Get time from NTP...");
  // Send packet
  udp.beginPacket(NTP_SRC, 123);
  udp.write(0x1B);
  udp.endPacket();
  // Wait response
  if (!ntp_wait_response()) {
    Serial.println("\nFailed receiving NTP packet.");
    return 0;
  }
   // Read response
  uint8_t buff[48];
  udp.read(buff, 48);
  // Process response
  uint32_t high_word = word(buff[40], buff[41]);
  uint32_t low_word = word(buff[42], buff[43]);
  uint32_t sec_since_1900 = high_word << 16 | low_word;
  const uint32_t years_x70 = 2208988800UL;
  uint32_t epoch = sec_since_1900 - years_x70;
  Serial.println("OK.");
  return epoch;
};

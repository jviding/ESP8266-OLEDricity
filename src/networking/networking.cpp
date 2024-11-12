#include "networking.h"


bool Networking::enable() {
  Serial.println("Network: Starting...");
  wifi_connect();
  HTTPS_req::enable();
  if (!NTP_time::enable()) {
    Serial.println("Network: Failed.");
    return false;
  }
  Serial.println("Network: Started.");
  delay(200);
  return true;
};

void Networking::disable() {
  Serial.println("Network: Disconnect.");
  wifi_disconnect();
}

bool Networking::get_time(int* time_now) {
  Serial.println("Network: Get time.");
  wifi_ensure_is_connected();
  if (NTP_time::get_finnish_time(time_now)) {
    Serial.println("Network: Ok.");
    return true;
  } else {
    Serial.println("Network: Failed.");
    return false;
  }
  
};

bool Networking::get_data(price_data_t** data) {
  Serial.println("Network: Get price data.");
  wifi_ensure_is_connected();
  if (HTTPS_req::get_price_data(data)) {
    Serial.println("Network: Ok.");
    return true;
  } else {
    Serial.println("Network: Failed.");
    return false;
  }
};

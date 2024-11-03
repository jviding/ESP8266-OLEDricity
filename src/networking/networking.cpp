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
  if (!NTP_time::get_finnish_time(time_now)) {
    Serial.println("Network: Failed.");
    return false;
  }
  return true;
};

bool Networking::get_data(price_data_t** data) {
  Serial.println("Network: Get price data.");
  wifi_ensure_is_connected();
  https_t* raw_data;
  bool res_ok = true;
  res_ok &= HTTPS_req::get_data(&raw_data) != -1;
  res_ok &= Parser::get_price_data(raw_data, data);
  if (!res_ok) {
    Serial.println("Network: Failed.");
  }
  return res_ok;
};

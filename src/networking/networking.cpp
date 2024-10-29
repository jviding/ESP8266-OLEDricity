#include "networking.h"


bool Networking::enable() {
  Serial.println("Network: Starting...");
  if (!NTP_time::enable()) {
    Serial.println("Network: Failed.");
    return false;
  } else {
    HTTPS_req::enable();
    Serial.println("Network: Started.");
    delay(500);
    return true;
  }  
};

void Networking::disable() {
  Serial.println("Network: Disconnect.");
  wifi_disconnect();
}

bool Networking::get_time(time_t* time) {
  Serial.println("Network: Get time.");
  wifi_ensure_is_connected();
  return NTP_time::get_finnish_time(time);
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

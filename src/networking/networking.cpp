#include "networking.h"


bool Networking::enable() {
  Serial.println("Network: Starting...");
  HTTPS_req::init();
  NTP_time::enable();
  bool res_ok = WiFi_ctrl::init();
  if (!res_ok) Serial.println("Network: No WiFi credentials.");
  return print_result(res_ok);
};

bool Networking::connect() {
  Serial.println("Network: Connect.");
  return print_result(WiFi_ctrl::connect());
};

bool Networking::disconnect() {
  Serial.println("Network: Disconnect.");
  return print_result(WiFi_ctrl::disconnect());
};

bool Networking::hotspot_enable(char* name, char** password, char** ip_address) {
  Serial.println("Network: HotSpot enable.");
  return print_result(WiFi_ctrl::hotspot_enable(name, password, ip_address)); 
};

bool Networking::hotspot_disable() {
  Serial.println("Network: HotSpot disable.");
  return print_result(WiFi_ctrl::hotspot_disable());
};

bool Networking::set_WiFi_SSID_and_password() {
  Serial.println("Network: Set WiFi credentials.");
  return print_result(WiFi_ctrl::set_WiFi_SSID_and_password()); 
};

bool Networking::get_time(int* time_now) {
  Serial.println("Network: Get time.");
  return print_result(WiFi_ctrl::connect() && NTP_time::get_finnish_time(time_now));
};

bool Networking::get_data(price_data_t** data) {
  Serial.println("Network: Get price data.");
  return print_result(WiFi_ctrl::connect() && HTTPS_req::get_price_data(data));
};

bool Networking::print_result(bool res_ok) {
  Serial.print("Network: ");
  Serial.println(res_ok ? "Ok." : "Failed.");
  return res_ok;
};

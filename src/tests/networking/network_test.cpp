#include "network_test.h"


bool Network_test::test_WiFi_reset_sequence() {
  Serial.println("Test WiFi: Reset sequence");
  bool res_ok = true;
  // Disconnect, if connected
  WiFi_ctrl::disconnect();
  Serial.println("Test WiFi: WiFi disconnected");
  delay(500);
  // Open HotSpot and print IP
  char* ip_address = nullptr;
  char* password = nullptr;
  res_ok = res_ok && WiFi_ctrl::hotspot_enable(&ip_address, &password);
  Serial.println("Test WiFi: HotSpot enabled");
  Serial.print(" - IP address: "); Serial.println(ip_address);
  Serial.print(" - Password: "); Serial.println(password);
  delete[] ip_address;
  delete[] password;
  delay(500);
  // Get new WiFi credentials
  res_ok = res_ok && WiFi_ctrl::set_WiFi_SSID_and_password();
  Serial.println("Test WiFi: New WiFi credentials were set");
  delay(500);
  // Disable HotSpot and connect to new WiFi
  WiFi_ctrl::hotspot_disable();
  Serial.println("Test server over WiFi: HotSpot disabled");
  delay(500);
  WiFi_ctrl::connect();
  Serial.println("Test server over WiFi: Connected to new WiFi");
  delay(500);
  return true;
};

void Network_test::test_get_and_print_price_data() {
  Networking::connect();
  return HTTPS_test::get_and_print_price_data();
};

void Network_test::test_get_and_print_time() {
  Networking::connect();
  return NTP_test::get_and_print_time();
};

bool Network_test::test_wifi_modes() {
  return WiFi_test::test_wifi_modes();
};

bool Network_test::test_wifi_eeprom() {
  return WiFi_test::test_eeprom();
};

bool Network_test::test_wifi_server_over_WiFi() {
  return WiFi_test::test_server_over_WiFi();
};

bool Network_test::test_wifi_server_over_HotSpot() {
  return WiFi_test::test_server_over_HotSpot();
};

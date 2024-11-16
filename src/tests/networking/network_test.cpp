#include "network_test.h"


bool Network_test::toggle_WiFi() {
  Serial.println("## Test WiFi: Connect");
  bool res_ok = WiFi_ctrl::connect();
  Serial.println("## Test WiFi: Connected");
  delay(500);
  Serial.println("## Test WiFi: Disconnect");
  res_ok = res_ok && WiFi_ctrl::disconnect();
  Serial.println("## Test WiFi: Disconnected");
  delay(500);
  return res_ok;
};

bool Network_test::test_WiFi_reset_sequence() {
  Serial.println("## Test WiFi: Test the WiFi reset sequence");
  bool res_ok = true;
  // Toggle current WiFi
  res_ok = toggle_WiFi();
  // Open HotSpot and print IP
  char* ip_address = nullptr;
  char* password = nullptr;
  Serial.println("## Test WiFi: HotSpot enable");
  res_ok = res_ok && WiFi_ctrl::hotspot_enable(&ip_address, &password);
  Serial.println("## Test WiFi: HotSpot enabled");
  delete[] ip_address;
  delete[] password;
  delay(500);
  // Get new WiFi credentials
  Serial.println("## Test WiFi: New WiFi credentials, get");
  res_ok = res_ok && WiFi_ctrl::set_WiFi_SSID_and_password();
  Serial.println("## Test WiFi: New WiFi credentials, set");
  delay(500);
  // Disable HotSpot
  Serial.println("## Test WiFi: HotSpot disable");
  res_ok = res_ok && WiFi_ctrl::hotspot_disable();
  Serial.println("## Test WiFi: HotSpot disabled");
  delay(500);
  // Toggle new WiFi
  res_ok = res_ok && toggle_WiFi();
  Serial.println("\n## Test  WiFi: COMPLETED");
  Serial.print(" - Result: "); Serial.println(res_ok ? "SUCCESS\n" : "FAILED\n");
  delay(500);
  return true;
};

void Network_test::test_get_and_print_price_data() {
  if (Networking::connect()) HTTPS_test::get_and_print_price_data();
  else Serial.println("## Test HTTPS: WiFi connection failed.");
};

void Network_test::test_get_and_print_time() {
  if (Networking::connect()) NTP_test::get_and_print_time();
  else Serial.println("## Test NTP: WiFi connection failed.");
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

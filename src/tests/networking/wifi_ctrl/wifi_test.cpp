#include "wifi_test.h"

bool WiFi_test::test_eeprom() {
  return Eeprom_test::test_read_write();
};

bool WiFi_test::test_server_over_WiFi() {
  Serial.println("Test server over WiFi: Connect");
  WiFi_ctrl::connect();
  Serial.println("Test server over WiFi: Connected"); 
  delay(500);
  return Server_test::test_web_service();
};

#include "wifi_test.h"


bool WiFi_test::toggle_wifi() {
  Serial.println("Test WiFi: Toggle WiFi");
  bool res_ok = WiFi_ctrl::connect();
  delay(500);
  res_ok = res_ok && WiFi_ctrl::disconnect();
  delay(500);
  return res_ok;
};

bool WiFi_test::toggle_hotspot() {
  Serial.println("Test WiFi: Toggle HotSpot");
  char* name = new char[12]{'E','l','e','c','t','r','i','c','u','b','e','\0'};
  char* pwd = nullptr;
  char* ip = nullptr;
  bool res_ok = WiFi_ctrl::hotspot_enable(name, &pwd, &ip);
  delay(500);
  delete[] name;
  delete[] pwd;
  delete[] ip;
  res_ok = res_ok && WiFi_ctrl::hotspot_disable();
  delay(500);
  return res_ok;
};

bool WiFi_test::test_wifi_modes() {
  bool res_ok = true;
  res_ok = res_ok && toggle_wifi();
  res_ok = res_ok && toggle_hotspot();
  res_ok = res_ok && toggle_wifi();
  res_ok = res_ok && toggle_hotspot();
  if (res_ok) {
    Serial.println("\n** Test WiFi modes: SUCCESS! **\n");
  } else {
    Serial.println("\n** Test WiFi modes: Something went wrong! **\n");
  }
  return res_ok;
};

bool WiFi_test::test_eeprom() {
  Serial.println("Test WiFi EEPROM: Reads and writes");
  return Eeprom_test::test_read_write();
};

bool WiFi_test::test_server_over_WiFi() {
  Serial.println("Test server over WiFi: Connect");
  bool res_ok = WiFi_ctrl::connect();
  Serial.println("Test server over WiFi: Connected"); 
  delay(500);
  Server_test::test_web_service();
  delay(500);
  Serial.println("Test server over WiFi: Disconnect");
  res_ok = res_ok && WiFi_ctrl::disconnect();
  if (res_ok) {
    Serial.println("Test server over WiFi: Disconnected");
    Serial.println("\n** Test server over WiFi: SUCCESS! **\n");
  } else {
    Serial.println("\n** Test server over WiFi: Something went wrong! **\n");
  }
  delay(500);
  return res_ok;
};

bool WiFi_test::test_server_over_HotSpot() {
  bool res_ok = true;
  char* name = new char[12]{'E','l','e','c','t','r','i','c','u','b','e','\0'};
  char* password = nullptr;
  char* ip_address = nullptr;
  Serial.println("Test server over HotSpot: Enable");
  res_ok = res_ok && WiFi_ctrl::hotspot_enable(name, &password, &ip_address);
  delete[] name;
  delete[] password;
  delete[] ip_address;
  Serial.println("Test server over HotSpot: Enabled");
  delay(500);
  Server_test::test_web_service();
  delay(500);
  Serial.println("Test server over HotSpot: Disable");
  res_ok = res_ok && WiFi_ctrl::hotspot_disable();
  Serial.println("Test server over HotSpot: Disabled");
  if (res_ok) {
    Serial.println("\n** Test server over HotSpot: SUCCESS! **\n");
  } else {
    Serial.println("\n** Test server over HotSpot: Something went wrong! **\n");
  }
  delay(500);
  return res_ok;
};

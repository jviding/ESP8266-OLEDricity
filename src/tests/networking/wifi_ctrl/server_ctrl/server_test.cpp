#include "server_test.h"


bool Server_test::test_web_service() {
  Serial.println("\n** WIFI SERVER TEST **\n");
  char* ssid = nullptr;
  char* pwd = nullptr;
  Serial.println("Test: Open the web form and submit WiFi credentials.");
  delay(500);
  Server_ctrl::run(&ssid, &pwd);
  delete[] ssid;
  delete[] pwd;
  Serial.println("Test: Completed.");
  return true;
};

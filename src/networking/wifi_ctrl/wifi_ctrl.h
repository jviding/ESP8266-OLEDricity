#pragma once

#include <ESP8266WiFi.h>
#include "eeprom_ctrl/eeprom_ctrl.h"
#include "server_ctrl/server_ctrl.h"

#include "../../secrets.h"
#define WIFI_SSID  SECRETS_WIFI_SSID
#define WIFI_PWD   SECRETS_WIFI_PWD


class WiFi_ctrl {
public:
  // Functions
  static bool init();
  static bool connect();
  static bool disconnect();
  static bool hotspot_enable(char** ip_address, char** password);
  static bool hotspot_disable();
  static bool set_WiFi_SSID_and_password();

private:
  // Variables
  static char* SSID;
  static char* PWD;

  // Functions
  static bool is_connected();
  static bool is_connecting();
  static bool try_connect();
  static void generate_random_8_digit_password(char** password);
  static void ip_address_to_str(IPAddress IP, char** ip_address);
};

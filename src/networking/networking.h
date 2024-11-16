#pragma once

#include "https_req/https_req.h"
#include "ntp_time/ntp_time.h"
#include "wifi_ctrl/wifi_ctrl.h"
#include "netStructs.h"

#include "../secrets.h"
#define WIFI_SSID  SECRETS_WIFI_SSID
#define WIFI_PWD   SECRETS_WIFI_PWD


/*
*  1. Connects to WiFi.
*  2. Requests price data from the API.
*  3. Reads the response to 'buffers_raw'.
*  4. Parses the data into a set of 'price_data_raw_t'.
*  5. Formats the 'price_data_raw_t' to 'price_data_t'.
*/


class Networking {
public:
  // Functions
  static bool enable();
  static bool connect();
  static bool disconnect();
  static bool hotspot_enable(char** ip_address, char** password);
  static bool hotspot_disable();
  static bool set_WiFi_SSID_and_password();

  static bool get_data(price_data_t** data);
  static bool get_time(int* time);

private:
  // Functions
  static bool print_result(bool res_ok);
};

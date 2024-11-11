#pragma once

#include <ESP8266WiFi.h>
#include <BearSSLHelpers.h>
#include <ESP8266HTTPClient.h>
#include "parser/parser.h"
#include "../netStructs.h"

#include "../../config.h"
#define API_URL   CONFIG_API_URL

#define BUFFERS_MAX_NUM   10
#define BUFFER_SIZE       512


// 1. Get electricity price data from external API.
// 2. Reads the data as raw binary to buffers.
// 3. Writes '\0' to end of last buffer, to signal EOF.


class HTTPS_req {
public:
  // Functions
  static void enable();
  static bool get_data(price_data_t** data);

private:
  // Variables
  static HTTPClient https;
  static BearSSL::WiFiClientSecure client;

  // Functions
  static int read_to_buffer(Stream* response, char* buff, size_t buff_size);
  static int read_to_buffers(Stream* response, char** buffs, size_t buffs_num, size_t buff_size);
  static int get_raw_data(char** buffs, size_t buffs_max_num, size_t buff_size);  
};

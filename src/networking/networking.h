#pragma once

#include <ESP8266WiFi.h>
#include <BearSSLHelpers.h>
#include <ESP8266HTTPClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Timezone.h>

#include "../secrets.h"
#define WIFI_SSID  SECRETS_WIFI_SSID
#define WIFI_PWD   SECRETS_WIFI_PWD

#define API_URL   "https://api.porssisahko.net/v1/latest-prices.json"
#define NTP_SRC   "pool.ntp.org"

#define BUFFERS_RAW_MAX_NUM   10
#define BUFFER_RAW_MAX_SIZE   512
#define PRICES_MAX_NUM        48

#define PRICE_MAX_LEN         10
#define TIME_MAX_LEN          14

/*
*  1. Connects to WiFi.
*  2. Requests price data from the API.
*  3. Reads the response to 'buffers_raw'.
*  4. Parses the data into a set of 'price_data_raw_t'.
*  5. Formats the 'price_data_raw_t' to 'price_data_t'.
*/


struct price_data_raw_t {
  char* price;
  char* time;
  bool  eof;
};

struct price_data_t {
  int  cents_x100;
  int  year;
  int  month;
  int  day;
  int  hour;
  bool eof;
};


class Networking {
public:
  // Variables
  static price_data_t** price_data;

  // Functions
  static void enable();
  static void disable();
  static bool update_data();
  static uint32_t get_time();

private:
  // Variables
  static price_data_raw_t** price_data_raw;
  static char** buffers_raw;
  static bool has_data;

  // Functions
  static void allocate_buffers();
  static void ensure_data_freed();

  /*
  * FORMAT
  * - Converts the 'price_data_raw_t' to 'price_data_t'
  */
  static int format_char_to_int(char str);
  static void format_set_price_x100(price_data_t* price_data, char* price_str);
  static void format_set_time(price_data_t* price_data, char* time_str);
  static bool format_is_older_than(price_data_t* price_data, price_data_t* compare);
  static void format_sort_oldest_to_latest(price_data_t** parsed, size_t num_items);
  static void format_price_data(price_data_t** parsed, price_data_raw_t** raw, size_t num_items);

  /*
  * DATA
  * - Parses raw response data into an array of 'price_data_raw_t'
  * - Note 1: Frees the memory allocated by HTTPS
  * - Note 2: Does NOT free the memory allocated for the new array
  */
  // Variables - Data
  static size_t char_ptr;
  static size_t buff_ptr;
  static bool buff_empty;
  // Functions - Data
  static char data_next_char(char** buffs_raw, size_t buffs_raw_num, size_t buffs_raw_size);
  static bool data_skip_until_char(char c, char** buffs_raw, size_t buffs_raw_num, size_t buffs_raw_size);
  static void data_str_truncate(char** str_ptr, size_t cpy_len);
  static bool data_read_until_char(char c, char** str_ptr, size_t max_len, char** buffs_raw, size_t buffs_raw_num, size_t buffs_raw_size);
  static void data_ensure_buffers_were_freed(char** buffs_raw, size_t buffs_raw_num, size_t buffs_raw_size);
  static bool data_parse(price_data_raw_t** buff_parsed, size_t buff_parsed_size, char** buffs_raw, size_t buffs_raw_num, size_t buffs_raw_size);

  /*
  * HTTPS
  * - Calls API and reads the raw response into a set of buffers.
  * - Note 1: Writes '\0' to the end of buffered data to signal EOF.
  * - Note 2: Does NOT free the allocated memory, if response was successfully read.
  */
  // Variables - HTTPS
  static HTTPClient https;
  static BearSSL::WiFiClientSecure client;
  // Functions - HTTPS
  static int https_read_to_buffer(Stream* response, char* buff, size_t buff_size);
  static int https_read_response(Stream* response, char** buffs, size_t buffs_num, size_t buff_size);
  static int https_call_API(char** buffs, size_t buffs_num, size_t buff_size);
  static void https_enable();

  /*
  * NTP
  * - Get time from external source
  */
  // Variables
  static WiFiUDP udp;
  static NTPClient ntpClient;
  // Functions - NTP
  static time_t ntp_get_epoch_time();
  static void ntp_enable();

  /*
  * WIFI
  * - Controls WiFi connectivity.
  */
  // Functions - WiFi
  static bool wifi_is_connected();
  static void wifi_connect();
  static void wifi_disconnect();
  static void wifi_ensure_is_connected(); 
};

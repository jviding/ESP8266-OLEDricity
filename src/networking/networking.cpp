#include "networking.h"

price_data_t** Networking::price_data;
price_data_raw_t** Networking::price_data_raw;
char** Networking::buffers_raw;
bool Networking::has_data = false;


void Networking::allocate_buffers() {
  buffers_raw = new char*[BUFFERS_RAW_MAX_NUM];
  price_data_raw = new price_data_raw_t*[PRICES_MAX_NUM];
  price_data = new price_data_t*[PRICES_MAX_NUM];
  Serial.println("Allocated pointers for data buffers.");
};

void Networking::enable() {
  Serial.println("Enabling Networking...");
  https_enable();
  ntp_enable();
  allocate_buffers();
  Serial.println("Networking enabled.");
  delay(100);
};

void Networking::ensure_data_freed() {
  if (has_data) {
    for (size_t i = 0; i < PRICES_MAX_NUM; i++) {
      delete price_data[i];
    }
    Serial.println("Freed price data.");
    has_data = false;
  }
};

bool Networking::update_data() {
  wifi_ensure_is_connected();
  ensure_data_freed();
  delay(100);
  // Read raw response data to 'buffers_raw'
  int buffers_raw_num = https_call_API(buffers_raw, BUFFERS_RAW_MAX_NUM, BUFFER_RAW_MAX_SIZE);
  if (buffers_raw_num == -1) {
    Serial.println("Failed fetching data from API.");
    return false;
  }
  // Parse the raw response data to an array of 'price_data_raw'
  // This will free all the memory allocated for the raw data
  bool res_ok = data_parse(price_data_raw, PRICES_MAX_NUM, buffers_raw, buffers_raw_num, BUFFER_RAW_MAX_SIZE);
  if (!res_ok) {
    Serial.println("Failed parsing raw response data.");
    return false;
  }
  // Parse the 'price_data_raw' to 'price_data'
  format_price_data(price_data, price_data_raw, PRICES_MAX_NUM);
  has_data = true;
  // Disconnect WiFi
  wifi_disconnect();
  return true;
};

uint32_t Networking::get_time() {
  wifi_ensure_is_connected();
  return ntp_get_epoch_time();
}

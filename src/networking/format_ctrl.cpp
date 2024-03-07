#include "networking.h"


int Networking::format_char_to_int(char str) {
  // ASCII conversion
  // '0' - '0' = 48 - 48 = 0
  // '1' - '0' = 49 - 48 = 1
  // ...
  // '9' - '0' = 57 - 48 = 9
  return str - '0';
};

void Networking::format_set_price_x100(price_data_t* price_data, char* price_str) {
  // Price is in format 'XXX.XXX', where the number of X may vary
  int result = 0;
  // Read until dot
  while (*price_str != '.') {
    result = result * 10 + format_char_to_int(*price_str);
    price_str++;
  }
  // Read 2x more values for x100
  price_str++;
  result = result * 10 + format_char_to_int(*price_str);
  price_str++;
  result = result * 10 + format_char_to_int(*price_str);
  // Set
  price_data->cents_x100 = result;
};

void Networking::format_set_time(price_data_t* price_data, char* time_str) {
  // Time is in format 'YYYY-MM-DDTHH'
  int time[] = {0, 0, 0, 0};
  // Read 1: year, 2: month, 3: day
  for (size_t i = 0; i < 3; i++) {
    while (*time_str != '-' && *time_str != 'T') {
      time[i] = time[i] * 10 + format_char_to_int(*time_str);
      time_str++;
    }
    time_str++; // Skip '-' or 'T'
  }
  // Read 4: hour
  time[3] = format_char_to_int(*time_str);
  time_str++;
  time[3] = time[3] * 10 + format_char_to_int(*time_str);
  // Set
  price_data->year  = time[0];
  price_data->month = time[1];
  price_data->day   = time[2];
  price_data->hour  = time[3];
};

bool Networking::format_is_older_than(price_data_t* price_data, price_data_t* compare) {
  int time_1 = 0;
  time_1 += price_data->year  * 1000000;
  time_1 += price_data->month * 10000;
  time_1 += price_data->day   * 100;
  time_1 += price_data->hour;
  int time_2 = 0;
  time_2 += compare->year  * 1000000;
  time_2 += compare->month * 10000;
  time_2 += compare->day   * 100;
  time_2 += compare->hour;
  return time_1 > time_2;
};

void Networking::format_sort_oldest_to_latest(price_data_t** parsed, size_t num_items) {
  for (size_t a = 0; a < num_items - 1; a++) {
    for (size_t b = 0; b < num_items - 1; b++) {
      if (format_is_older_than(parsed[b], parsed[b + 1])) {
        price_data_t* temp = parsed[b];
        parsed[b] = parsed[b + 1];
        parsed[b + 1] = temp;
      }
    }
  }
};

void Networking::format_price_data(price_data_t** parsed, price_data_raw_t** raw, size_t num_items) {  
  Serial.print("Formatting response...");
  for (size_t i = 0; i < num_items; i++) {
    // Allocate new price_data_t
    price_data_t* price_data = new price_data_t;
    price_data->eof = 0;
    // Set price data
    format_set_price_x100(price_data, raw[i]->price);
    // Set time data
    format_set_time(price_data, raw[i]->time);
    // Free memory of raw
    delete[] raw[i]->price;
    delete[] raw[i]->time;
    delete raw[i];
    // Set new price_data_t
    parsed[i] = price_data;
  }
  parsed[num_items - 1]->eof = 1;
  Serial.print("Formatted.");
  format_sort_oldest_to_latest(price_data, PRICES_MAX_NUM);
  Serial.print("Sorted.");
  Serial.println("Buffers freed.");
};

#pragma once

#include <Arduino.h>
#include "../https_req/https_req.h"


struct price_data_t {
  int  cents_x100;
  int  time;
  price_data_t* next;
  price_data_t* prev;
};


class Parser {
public:
  // Functions
  static bool get_price_data(https_t** raw_data, price_data_t** parsed_data);

private:
  // CONVERT
  // Functions
  static int char_to_int(char c);
  static int str_to_int_x100(char* str);
  static int str_time_to_int(char* str);

  // PARSE
  // Variables
  static price_data_t* price_data_first;
  // Functions
  static bool has_next_json();
  static bool parse_next_json(price_data_t* data);
  static bool parse_response(price_data_t** first);
  static void sort_data_time_ascending(price_data_t** data);
  static void free_buffers();

  // READ
  // Variables
  static char** buffs;
  static size_t buffs_num;
  static size_t buff_size;
  static size_t char_ptr;
  static size_t buff_ptr;
  // Functions
  static void init_read(https_t* raw_data);
  static bool next_buffer();
  static bool next_char(char* c);
  static bool skip_until_char(char c);
  static bool read_until_char(char c, char** ptr);
  static void append_char(char** ptr, size_t len, char c);

  // SORT
  // Functions
  static void swap(price_data_t* node_1, price_data_t* node_2);
  static bool should_swap(price_data_t* node_1, price_data_t* node_2);
  static void sort_by_time_ascending(price_data_t** first);
};

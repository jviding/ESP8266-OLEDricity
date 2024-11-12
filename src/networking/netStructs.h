#pragma once

struct price_data_t {
  int  cents_x100;
  int  time;
  price_data_t* next;
  price_data_t* prev;
};

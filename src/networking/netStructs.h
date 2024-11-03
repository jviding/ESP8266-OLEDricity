#pragma once

struct https_t {
  int num;
  int size;
  char** buffs;
};

struct price_data_t {
  int  cents_x100;
  int  time;
  price_data_t* next;
  price_data_t* prev;
};

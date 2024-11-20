#pragma once

#include "../../networking/netStructs.h"

struct dataset_t {
  int size;
  int price_max;
  int price_now;
  int time_now;
  price_data_t* price_data;
};

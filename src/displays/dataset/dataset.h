#pragma once

#include <Arduino.h>
#include "dataset_t.h"


class Dataset {
  public:
    // Functions
    static int create_dataset(dataset_t** dataset, int dataset_size, price_data_t* data, int time_now);

  private:
    // Functions
    static bool set_ptr_to_data_now(dataset_t* dataset, price_data_t* data, int time_now);
    static void try_shift_data_ptr_one_left(dataset_t* dataset);
    static bool set_price_max(dataset_t* dataset, int dataset_size);
};

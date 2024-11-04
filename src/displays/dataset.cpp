#include "displays.h"


bool Displays::set_ptr_to_data_now(dataset_t* dataset, price_data_t* data, int time_now) {
  while (data != nullptr) {
    if (data->time == time_now) {
      dataset->time_now = time_now;
      dataset->price_now = data->cents_x100;
      dataset->price_data = data;
      return true;
    }
    data = data->next;
  }
  Serial.println("Dataset: Failed finding data for current time.");
  return false;
};

void Displays::try_shift_data_ptr_one_left(dataset_t* dataset) {
  if ((dataset->price_data)->prev != nullptr) {
    dataset->price_data = (dataset->price_data)->prev;
    return;
  }
  Serial.println("Dataset: Failed shifting dataset ptr one left.");
};

bool Displays::set_price_max(dataset_t* dataset, int dataset_size) {
  int val = 0;
  bool res_ok = true;
  price_data_t* temp = dataset->price_data;
  for (int i = 0; i < dataset_size; i++) {
    if (temp == nullptr) {
      Serial.println("Dataset: Unexpected EOF while resolving max price.");
      res_ok = false;
      break;
    }    
    if (temp->cents_x100 > val) {
      val = temp->cents_x100;
    }
    temp = temp->next;
  }
  dataset->price_max = val;
  dataset->size = dataset_size;
  return res_ok;
};

// Return 0: No data matching time_now
// Return 1: Success
// Return 2: Success, but with dataset unexpected EOF
int Displays::create_dataset(dataset_t** dataset, price_data_t* data, int time_now) {
  if (!set_ptr_to_data_now(*dataset, data, time_now)) return 0;
  try_shift_data_ptr_one_left(*dataset);
  if (!set_price_max(*dataset, CHART_PILLARS_NUM)) return 2;
  return 1;
};

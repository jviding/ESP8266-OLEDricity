#include "displays.h"


bool Displays::set_ptr_to_data_now(dataset_t* dataset, price_data_t* data, int time_now) {
  while (data->next != nullptr) {
    if (data->time == time_now) {
      (*dataset).time_now = time_now;
      (*dataset).price_now = data->cents_x100;
      (*dataset).price_data = &data;
      return true;
    }
  }
  Serial.println("Dataset: Failed finding data for current time.");
  return false;
};

void Displays::try_shift_data_ptr_one_left(dataset_t* dataset) {
  if ((*(dataset->price_data))->prev != nullptr) {
    *(dataset->price_data) = (*(dataset->price_data))->prev;
    return;
  }
  Serial.println("Dataset: Failed shifting dataset ptr one left.");
};

bool Displays::set_price_max(dataset_t* dataset, int dataset_size) {
  int val = 0;
  price_data_t* temp = *(dataset->price_data);
  for (int i = 0; i < dataset_size; i++) {
    if (temp->cents_x100 > val) {
      val = temp->cents_x100;
    }
    temp = temp->next;
    if (temp == nullptr) {
      Serial.println("Dataset: Unexpected EOF while resolving max price.");
      return false;
    }
  }
  dataset->price_max = val;
  dataset->size = dataset_size;
  return true;
};

bool Displays::create_dataset(dataset_t** dataset, price_data_t* data, int time_now) {
  *dataset = new dataset_t;
  bool res_ok = true;
  res_ok &= set_ptr_to_data_now(*dataset, data, time_now);
  try_shift_data_ptr_one_left(*dataset);
  res_ok &= set_price_max(*dataset, CHART_PILLARS_NUM);
  if (!res_ok) {
    Serial.println("Dataset: Failed.");
    delete *dataset;
  }
  return res_ok;
};

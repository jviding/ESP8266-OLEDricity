#include "chart.h"

int Chart::price_max;


int Chart::to_data_time(time_t time_now) {
  int time = 0;                         // ----------
  time += year(time_now)  *100*100*100; // YYYY------
  time += month(time_now) *100*100;     // ----MM----
  time += day(time_now)   *100;         // ------DD--
  time += hour(time_now);               // --------HH
  return time;                          // YYYYMMDDHH
};

void Chart::delete_until_first(price_data_t** data, time_t time_now) {
  while (*data != nullptr) {
    if ((*data)->time == to_data_time(time_now)) break;
    if ((*data)->prev != nullptr) delete (*data)->prev;
    *data = (*data)->next;
  }
  if ((*data)->prev != nullptr) *data = (*data)->prev;
};

void Chart::set_price_max(price_data_t** data) {
  price_max = 0;
  for (size_t i = 0; i < DATASET_SIZE - 1; i++) {
    if (data != nullptr) {
      if ((*data)->cents_x100 > price_max) price_max = (*data)->cents_x100;
      *data = (*data)->next;
    }
  }
  // Round up to full cents (+100).
  // I.e., 12.2, 12.4, 12.6 wouldn't all be just 12.
  price_max += 100;
  // Set limits in full cents, upper 99, lower 10
  price_max = price_max > 99 ? 99 : price_max;
  price_max = price_max < 10 ? 10 : price_max;
};

void Chart::delete_after_last(price_data_t** data) {
  while (*data != nullptr && (*data)->next != nullptr) {
    *data = (*data)->next;
    delete (*data)->prev;
  }
  if (*data != nullptr) delete *data;
};

void Chart::create_dataset(price_data_t** data, time_t time_now) {
  price_data_t* temp = *data;
  // Find first in dataset
  delete_until_first(&temp, time_now);
  *data = temp;
  // Set price_max in dataset
  set_price_max(&temp);
  // Delete what overflows dataset
  delete_after_last(&temp);
};

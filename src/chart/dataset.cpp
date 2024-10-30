#include "chart.h"


int Chart::to_data_time(time_t time_now) {
  int time = 0;                         // ----------
  time += year(time_now)  *100*100*100; // YYYY------
  time += month(time_now) *100*100;     // ----MM----
  time += day(time_now)   *100;         // ------DD--
  time += hour(time_now);               // --------HH
  return time;                          // YYYYMMDDHH
};

void Chart::set_first(price_data_t** data, time_t time_now) {
  while (*data != nullptr) {
    if ((*data)->time == to_data_time(time_now)) break;
    if ((*data)->prev != nullptr) delete (*data)->prev;
    *data = (*data)->next;
  }
  if ((*data)->prev != nullptr) *data = (*data)->prev;
};

void Chart::set_price_max(price_data_t* data, int* price_max) {
  *price_max = 0;
  price_data_t* temp = data;
  for (size_t i = 0; i < DATASET_SIZE - 1; i++) {
    if (temp != nullptr) {
      if (temp->cents_x100 > *price_max) {
        *price_max = data->cents_x100;
      }
      temp = temp->next;
    }
  }
  // Round up to full cents (+100).
  // I.e., 12.2, 12.4, 12.6 wouldn't all be just 12.
  *price_max += 100;
  // Set limits in full cents, upper 99, lower 10
  *price_max = *price_max > 99 ? 99 : *price_max;
  *price_max = *price_max < 10 ? 10 : *price_max;
};

void Chart::create_dataset(price_data_t** data, time_t time_now, int* price_max) {
  set_first(data, time_now);
  set_price_max(*data, price_max);
};

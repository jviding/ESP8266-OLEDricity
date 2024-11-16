#include "displays_test.h"


void Displays_test::test_displays_with_data_fast_loop() {


  /*bool res_ok = true;
  // Time
  int time_now = 0;
  res_ok &= Networking::get_time(&time_now);
  // Data
  price_data_t* data = nullptr;
  res_ok &= Networking::get_data(&data);
  // Loop until no data
  while (res_ok) {
    // Draw
    res_ok = Displays::draw(data, time_now) != 0;
    // Next hour
    if (time_now % 100 == 23) {
      time_now += 100 - 23;
    } else {
      time_now++;
    }
    // Wait
    delay(200);
  }
  // Clear memory
  while (data != nullptr) {
    price_data_t* temp = data->next;
    delete data;
    data = temp;
  }*/
};

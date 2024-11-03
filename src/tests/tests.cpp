#include "tests.h"


void Tests::debug_print_heap() {
  uint32_t heap = ESP.getFreeHeap();
  Serial.println("\n");
  Serial.print("Free heap: "); Serial.println(heap);
  Serial.println("\n");
};

void Tests::print_time(int time_now) {
  Serial.println("\n");
  Serial.print("Time now: "); Serial.println(time_now);
  Serial.println("\n");
};

void Tests::print_price_data(price_data_t* data) {
  Serial.println("\n\n");
  Serial.println("Price Data:");
  int counter = 1;
  while (data != nullptr) {
    int full = data->cents_x100 / 100;
    int deci = data->cents_x100 % 100;
    if (deci < 0) deci *= -1;
    // Print
    Serial.print(counter); Serial.print(": ");
    Serial.print(data->time); Serial.print(" - ");
    Serial.print(full); Serial.print("."); Serial.println(deci);
    // Counter
    counter++;
    data = data->next;
  }
  Serial.print("\n\n");
};

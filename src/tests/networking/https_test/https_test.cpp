#include "https_test.h"


void HTTPS_test::get_and_print_price_data() {
  // Get data
  price_data_t* data = nullptr;
  HTTPS_req::get_price_data(&data);
  // Print
  Serial.println("\n\n");
  Serial.println("Price Data:");
  int counter = 1;
  price_data_t* temp = data;
  while (temp != nullptr) {
    // Check for negative price
    bool is_negative = false;
    if (temp->cents_x100 < 0) {
      is_negative = true;
      temp->cents_x100 *= -1;
    }
    // Get whole and decimal numbers
    int full = temp->cents_x100 / 100;
    int deci = temp->cents_x100 % 100;
    // Print row index
    if (counter < 10) Serial.print(" ");
    Serial.print(counter); Serial.print(": ");
    // Print time
    Serial.print(temp->time); Serial.print(" ");
    // Print price
    if (is_negative) Serial.print("-");
    Serial.print(full);
    Serial.print(".");
    if (deci < 10) Serial.print("0");
    Serial.println(deci);
    // Counter
    counter++;
    temp = temp->next;
  }
  Serial.print("\n\n");
  // Free memory
  while (data != nullptr) {
    temp = data->next;
    delete data;
    data = temp;
  }
  delay(2000);
};

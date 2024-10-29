#include "parser.h"


/*
* HTTPS response is in format:
*   {"prices":[{},{}, ... ,{}]}
* 
* Where each JSON in the array is: 
*   {"price":XXX.XX,"startDate":"YYYY-MM-DD-THH:00:00:000Z","endDate":"YYYY-MM-DD-THH:00:00:000Z"}
*
* Where Price:
*  - Can be a negative value (i.e., -0.188).
*  - Can have a varying number of digits on both sides of the dot.
*/

bool Parser::has_next_json() {
  if (!!skip_until_char('{')) {
    return true;
  }
  Serial.println("Parser: No more JSONs to read.");
  return false;
};

bool Parser::parse_next_json(price_data_t* data) {
  char* price = nullptr;
  char* time = nullptr;
  bool res_ok = true;
  // Read price
  res_ok &= skip_until_char(':');
  res_ok &= read_until_char(',', &price);
  // Read time (startDate)
  res_ok &= skip_until_char(':');
  res_ok &= skip_until_char('"');
  res_ok &= read_until_char(':', &time);
  // Read until end of JSON
  res_ok &= skip_until_char('}');
  if (res_ok) {
    data->cents_x100 = str_to_int_x100(price);
    data->time = str_time_to_int(time);
  } else {
    Serial.println("Parser: Failed parsing JSON.");
  }
  if (price != nullptr) delete[] price;
  if (time != nullptr) delete[] time;
  return res_ok;
};

bool Parser::parse_response(price_data_t** first) {
  price_data_t* data_prev = nullptr;
  price_data_t* data_next = nullptr;
  bool res_ok = true;
  // Skip until start of array
  res_ok &= skip_until_char('[');
  // Read JSON by JSON
  while(res_ok && has_next_json()) {
    data_next = new price_data_t;
    data_next->next = nullptr;
    data_next->prev = nullptr;
    if (data_prev != nullptr) {
      data_prev->next = data_next; // Create links
      data_next->prev = data_prev; // Create links
    } else {
      *first = data_next;          // Set first in linked list
    }
    res_ok &= parse_next_json(data_next);
    data_prev = data_next;
  }
  if (!res_ok) {
    Serial.println("Parser: Releasing memory allocated for parsed data.");
    while (*first != nullptr) {
      price_data_t* temp = (*first)->next;
      delete *first;
      *first = temp;
    }
  }
  return res_ok;
};

bool Parser::get_price_data(https_t* raw_data, price_data_t** parsed_data) {
  Serial.println("Parser: Parsing response...");
  init_read(raw_data);
  if (!parse_response(parsed_data)) {
    Serial.println("Parser: Parsing failed.");
    return false;
  }
  sort_by_time_ascending(parsed_data);
  Serial.println("Parser: Parsing completed.");
  return true;
};

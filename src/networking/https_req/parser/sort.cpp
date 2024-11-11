#include "parser.h"


void Parser::swap(price_data_t* node_1, price_data_t* node_2) {
  int temp;
  // Swap cents_x100
  temp = node_1->cents_x100;
  node_1->cents_x100 = node_2->cents_x100;
  node_2->cents_x100 = temp;
  // Swap time
  temp = node_1->time;
  node_1->time = node_2->time;
  node_2->time = temp;
};

bool Parser::should_swap(price_data_t* node_1, price_data_t* node_2) {
  return node_1->time > node_2->time;
};

void Parser::sort_by_time_ascending(price_data_t** data) {
  price_data_t* temp = *data;
  while (temp->next != nullptr) {
    if (should_swap(temp, temp->next)) {
      swap(temp, temp->next);
      if (temp->prev != nullptr) {
        temp = temp->prev;
      }
    } else {
      temp = temp->next;
    }
  }
};

#include "networking.h"

/*
* NOTE:
*  Memory allocated for the raw data must be released DURING parsing.
*  There's not enough memory for both the raw and parsed data the same time.
*/

size_t Networking::char_ptr;
size_t Networking::buff_ptr;
bool Networking::buff_empty;


// Reads next char in raw buffers, until '\0'.
// Immediately frees a raw buffer once all its characters have been read.
char Networking::data_next_char(char** buffs_raw, size_t buffs_raw_num, size_t buffs_raw_size) {
  // If buffer is already empty
  if (buff_empty) {
    return '\0';
  }
  // If char_ptr exceeded size of buffer
  if (char_ptr == buffs_raw_size) {
    delete[] buffs_raw[buff_ptr];     // -> Free current
    buff_ptr++;                       // -> Move to next
    char_ptr = 0;                     // -> Reset char_ptr
  }
  // If buff_ptr exceeded number of buffers
  if (buff_ptr == buffs_raw_num) {
    Serial.println("\nUnexpected end of buffers while parsing raw response data.");
    buff_empty = true;
    return '\0';
  }
  // Read char and move char_ptr to next
  char next_char = buffs_raw[buff_ptr][char_ptr];
  char_ptr++;
  // If char is EOF, free the buffer
  if (next_char == '\0') {
    delete[] buffs_raw[buff_ptr];
    buff_empty = true;
  }
  return next_char;
};

// Reads next char until the delimiter 'char c' is met.
// The delimiter is also read, meaning that the 'next char' will be the once after.
bool Networking::data_skip_until_char(char c, char** buffs_raw, size_t buffs_raw_num, size_t buffs_raw_size) {
  char current;
  while ((current = data_next_char(buffs_raw, buffs_raw_num, buffs_raw_size)) != '\0') {
    if (current == c) {
      return true;
    }
  }
  Serial.print("\nFailed skipping until '"); Serial.write(c); Serial.println("', unexpected EOF.");
  return false;
};

void Networking::data_str_truncate(char** str_ptr, size_t cpy_len) {
  // Create new truncated buffer
  char* temp = new char[cpy_len + 1];       // +1 for EOF
  temp[cpy_len] = '\0';                     // Write EOF
  // Copy old to new
  for (size_t i = 0; i < cpy_len; i++) {
    temp[i] = (*str_ptr)[i];
  }
  // Free old, and replace with new
  delete[] *str_ptr;
  *str_ptr = temp;
};

// Reads next char to 'char** str_ptr' until the delimiter 'char c' is met.
// Returns false, if max_len is reached before the delimiter.
bool Networking::data_read_until_char(char c, char** str_ptr, size_t max_len, char** buffs_raw, size_t buffs_raw_num, size_t buffs_raw_size) {
  // Read next chars to temp
  char* temp = new char[max_len];
  // Start reading
  for (size_t i = 0; i < max_len; i++) {
    // Read next char
    char next_char = data_next_char(buffs_raw, buffs_raw_num, buffs_raw_size);
    // If next char is the delimiter
    if (next_char == c) {
      // Truncate temp to correct size
      data_str_truncate(&temp, i);
      // Set it as the return value
      *str_ptr = temp;
      return true;
    }
    // If next char is unexpected EOF
    if (next_char == '\0') {
      Serial.print("\nFailed reading until '"); Serial.write(c); Serial.println("', unexpected EOF.");
      delete[] temp;
      return false;
    }
    // Write to temp and continue reading
    temp[i] = next_char;
  }
  // Exceeded max length, overflow
  Serial.print("\nFailed reading until '"); Serial.write(c); Serial.println("', value too long.");
  delete[] temp;
  return false;
};

void Networking::data_ensure_buffers_were_freed(char** buffs_raw, size_t buffs_raw_num, size_t buffs_raw_size) {
  while (data_next_char(buffs_raw, buffs_raw_num, buffs_raw_size) != '\0') {
    ; // Until EOF
  }
};

/*
* The full response is:
*   {"prices":[{},{}, ... ,{}]}
* 
* Where each JSON in the array is: 
*   {"price":XXX.XX,"startDate":"YYYY-MM-DD-THH:00:00:000Z","endDate":"YYYY-MM-DD-THH:00:00:000Z"}
*
* Price can have a varying number of digits on both sides of the dot.
*/

bool Networking::data_parse(price_data_raw_t** parsed, size_t parsed_num, char** buffs_raw, size_t buffs_raw_num, size_t buffs_raw_size) {
  Serial.print("Parsing response...");
  // Reset pointers
  char_ptr = 0;
  buff_ptr = 0;
  buff_empty = false;
  // Set value limits
  size_t price_len = PRICE_MAX_LEN;
  size_t time_len = TIME_MAX_LEN;
  // Scroll to start of JSON array
  data_skip_until_char('[', buffs_raw, buffs_raw_num, buffs_raw_size);
  // Then read JSON by JSON
  bool res_ok = true;
  size_t i;
  for (i = 0; i < parsed_num; i++) {
    // Create new price data
    price_data_raw_t* data = new price_data_raw_t;
    data->eof = false;
    // Read price
    char* price = nullptr;
    res_ok &= data_skip_until_char(':', buffs_raw, buffs_raw_num, buffs_raw_size);
    res_ok &= data_read_until_char(',', &price, price_len, buffs_raw, buffs_raw_num, buffs_raw_size);
    // Read time (startDate)
    char* time = nullptr;
    res_ok &= data_skip_until_char(':', buffs_raw, buffs_raw_num, buffs_raw_size);
    res_ok &= data_skip_until_char('"', buffs_raw, buffs_raw_num, buffs_raw_size);
    res_ok &= data_read_until_char(':', &time, time_len, buffs_raw, buffs_raw_num, buffs_raw_size);
    // Check for errors
    if (!res_ok) {
      Serial.println("\nFailed parsing, something went wrong.");
      // Free all allocated memory
      for (size_t a = 0; a < i; a++) {
        delete[] parsed[a]->price;
        delete[] parsed[a]->time;
        delete parsed[a];
      }
      delete[] price;
      delete[] time;
      delete data;
      break;
    }
    // Save price data
    data->price = price;
    data->time = time;
    parsed[i] = data;
    // Scroll to end of JSON
    res_ok &= data_skip_until_char('}', buffs_raw, buffs_raw_num, buffs_raw_size);
  }
  // Set last item as EOF
  if (res_ok) {
    parsed[i - 1]->eof = true;
  }
  Serial.print("Parsed.");
  // Ensure all raw buffers were freed
  data_ensure_buffers_were_freed(buffs_raw, buffs_raw_num, buffs_raw_size);
  Serial.println("Freed raw buffers.");
  return res_ok;
};

#include "parser.h"

/*
* NOTE:
*  Releases buffers while reading.
*  Buffer is released when its last char is read.
*  This prevents the ESP8266 from running out of memory.
*  The raw and read data don't fit in memory the same time.
*/

char** Parser::buffs;
size_t Parser::buffs_num;
size_t Parser::buff_size;
size_t Parser::char_ptr;
size_t Parser::buff_ptr;


void Parser::init_read(https_t* raw_data) {
  buffs = raw_data->buffs;
  buffs_num = raw_data->num;
  buff_size = raw_data->size;
  char_ptr = 0;
  buff_ptr = 0;
  delete raw_data;
};

bool Parser::next_buffer() {
  delete[] buffs[buff_ptr];     // Free current
  buffs[buff_ptr] = nullptr;    //  and set nullptr
  buff_ptr++;                   // Move buff_ptr to next
  char_ptr = 0;                 //  and reset char_ptr
  // Check next buffer exists
  if (buff_ptr == buffs_num) {
    Serial.println("Parser: Unexpected end of buffers.");
    free_buffers();
    return false;
  }
  return true;
};

bool Parser::next_char(char* c) {
  // If end of buffer, move to next
  if (char_ptr == buff_size && !next_buffer()) {
    Serial.println("Parser: Failed reading next char.");
    return false;
  }
  // Read next char
  *c = buffs[buff_ptr][char_ptr];
  char_ptr++;
  // If EOF, free the last buffer
  if (*c == '\0') {
    Serial.println("Parser: Buffers EOF reached.");
    free_buffers();
  }
  return true;
};

bool Parser::skip_until_char(char c) {
  char current;
  while (!!next_char(&current) && current != '\0') {
    if (current == c) {
      return true;
    }
  }
  //Serial.print("Parser: Failed skipping until '"); Serial.print(c); Serial.println("', unexpected EOF.");
  return false;
};

void Parser::append_char(char** ptr, size_t len, char c) {
  char* temp = new char[len+1];
  for (size_t i = 0; i < len-1; i++) {
    temp[i] = (*ptr)[i];
  }
  temp[len-1] = c;
  temp[len] = '\0';
  delete[] *ptr;
  *ptr = temp;
};

bool Parser::read_until_char(char c, char** ptr) {
  char current;
  size_t len = 0;
  // Start with an empty string
  char* read = new char[1];
  read[0] = '\0';
  // Then append char by char
  while (!!next_char(&current) && current != '\0') {
    len++;
    if (current == c) {
      *ptr = read;
      return true;
    } else {
      append_char(&read, len, current);
    }
  }
  delete[] read;
  //Serial.print("Parser: Failed reading until '"); Serial.print(c); Serial.println("', unexpected EOF.");
  return false;
};

void Parser::free_buffers() {
  Serial.println("Parser: Releasing buffers allocated for raw data.");
  for (size_t i = 0; i < buffs_num; i++) {
    if (buffs[i] != nullptr) delete[] buffs[i];
  }
  delete[] buffs;
};
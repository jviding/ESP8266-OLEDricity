#include "parser.h"


int Parser::char_to_int(char c) {
  // ASCII conversion
  // '0' - '0' = 48 - 48 = 0
  // '1' - '0' = 49 - 48 = 1
  // ...
  // '9' - '0' = 57 - 48 = 9
  return c - '0';
};

int Parser::str_to_int_x100(char* str) {
  // Price can be 'XX' or 'X.XXX', where number of X vary
  int result = 0;
  // Check if price is negative
  bool is_negative = false;
  if (*str == '-') {
    is_negative = true;
    str++;
  }
  // Read until dot or EOF
  while (*str != '.') {
    if (*str == '\0') {                             // If EOF, no decimals
      return result * 100 * (is_negative ? -1 : 1); // Return just x100
    }
    result = result * 10 + char_to_int(*str);
    str++;
  }
  // Append 2x decimals, for x100
  bool has_dec_1 = *(str + 1) != '\0';                  // Has first decimal?
  bool has_dec_2 = has_dec_1 && *(str + 2) != '\0';     // Has second decimal?
  bool has_dec_3 = has_dec_2 && *(str + 3) != '\0';
  int dec_1 = has_dec_1 ? char_to_int(*(str + 1)) : 0;  // If has, convert to int
  int dec_2 = has_dec_2 ? char_to_int(*(str + 2)) : 0;  // Else, set to 0
  int dec_3 = has_dec_3 ? char_to_int(*(str + 3)) : 0;
  result = result * 10 + dec_1;
  result = result * 10 + dec_2;
  if (dec_3 >= 5) result+= 1;                           // Round 2nd decimal up
  return result * (is_negative ? -1 : 1);
};

int Parser::str_time_to_int(char* str) {
  // Time is in format 'YYYY-MM-DDTHH'
  int result = 0;
  // Read to int as 'YYYYMMDDHH'
  while (*str != '\0') {
    if (*str != '-' && *str != 'T') {
      result = result * 10 + char_to_int(*str);
    }
    str++;
  }
  return result;
};

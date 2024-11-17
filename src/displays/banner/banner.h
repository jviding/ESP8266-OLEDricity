#pragma once

#include "U8g2lib.h"
#include <Wire.h>


#define X_BANNER_MAX   127
#define Y_BANNER_MAX   31
 

class Banner {
public:
  // Functions
  static void init();
  static void power_up();
  static void power_down();
  static void draw(int price_x100);

  // MESSAGES
  static void write_hotspot_message();

private:
  // Variables
  static U8G2_SH1106_128X32_VISIONOX_F_HW_I2C display;

  // Functions
  static int get_price_x100_num_of_digits_in_full_cents(int price_x100);
  static int get_price_x100_num_of_digits_in_decimals(int price_x100);
  static char int_to_char(int val);
  static void price_x100_to_str(char** str, int price_x100);
  static void draw_price(int price_x100);

  // MESSAGES
  static int get_X_offset_to_center_text(const char* text);
};
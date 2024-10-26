#pragma once

#include "U8g2lib.h"
#include <Wire.h>
#include "time.h"

#define X_BANNER_MAX   127
#define Y_BANNER_MAX   31
 

class Banner {
public:
  // Functions
  static void init();
  static void power_up();
  static void power_down();
  static void draw(int price_x100);

private:
  // Variables
  static U8G2_SH1106_128X32_VISIONOX_F_HW_I2C display;

  // Functions
  static int get_num_of_digits(int val);
  static char get_int_as_char(int val);
  static char* get_int_as_str(int val);
  static void draw_price(int price_x100);
};
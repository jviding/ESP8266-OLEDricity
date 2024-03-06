#pragma once

#include "U8g2lib.h"
#include <Wire.h>
#include "../networking/networking.h"

#define X_MAX   127
#define Y_MAX   63

#define Y_PLOT_MAX  (Y_MAX - 8)

class Chart {
public:
  // Functions
  static void init();
  static void draw();


private:
  // Variables
  static U8G2_SH1106_128X64_NONAME_F_HW_I2C display;
  static int max_price;
  static price_data_t** data;

  // Functions
  static void set_max_price();
  static void draw_y_axis();
  static void draw_x_axis();
  static void draw_xy_mid();
  static void draw_pillar(int val, int x);
  static void draw_pillars();  
};
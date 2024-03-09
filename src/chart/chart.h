#pragma once

#include "U8g2lib.h"
#include <Wire.h>
#include "time.h"
#include "../networking/networking.h"

#define X_CHART_MAX  127
#define Y_CHART_MAX  63
#define Y_PLOT_MAX   (Y_CHART_MAX - 8)

#define PILLARS_NUM 19


class Chart {
public:
  // Functions
  static void init();
  static void draw(price_data_t** price_data, uint32_t current_time);

private:
  // Variables
  static U8G2_SH1106_128X64_NONAME_F_HW_I2C display;
  static int max_price;
  static price_data_t** data;
  static time_t time_now;
  static size_t data_now;
  static size_t data_from;
  static size_t data_to;

  // Functions
  static void set_time_and_data_ptrs();
  static void set_max_price();
  static char* get_int_as_label(int val);
  static int get_pillar_height(int price);
  static void draw_y_axis_mid();
  static void draw_axis();
  static void draw_x_label(int hour, int x);
  static void draw_empty_pillar(int price, int x);
  static void draw_solid_pillar(int price, int x);
  static void draw_pillar(size_t index, int price, int x);
  static void draw_pillars();
};
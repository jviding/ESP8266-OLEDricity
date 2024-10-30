#pragma once

#include "U8g2lib.h"
#include <Wire.h>
#include "time.h"
#include "../networking/networking.h"

#define SCREEN_X_MIN 0
#define SCREEN_X_MAX 127
#define SCREEN_Y_MIN 0
#define SCREEN_Y_MAX 63

#define AXIS_X_MIN 10
#define AXIS_X_MAX 127
#define AXIS_Y_MIN 0
#define AXIS_Y_MAX (SCREEN_Y_MAX - 8)

#define PILLARS_NUM 19
#define DATASET_SIZE 19


class Chart {
public:
  // Functions
  static void init();
  static void draw(price_data_t** data, uint32_t time_now);

private:
  // Variables
  static U8G2_SH1106_128X64_NONAME_F_HW_I2C display;
  static int price_max;

  // Functions
  static char* int_to_label(int value);
  static void draw_XY_axis();
  static void draw_Y_labels();
  static int get_Y_offset(int price);
  static void draw_pillar_empty(int y_offset, int x_offset);
  static void draw_pillar_solid(int y_offset, int x_offset);
  static void draw_X_label(int hour, int x_offset);
  static void draw_pillars(price_data_t* dataset, int data_time);
  static void draw_y_mid();  

  // DATASET
  // Functions
  static int to_data_time(time_t time_now);
  static void set_first(price_data_t** data, time_t time_now);
  static void set_price_max(price_data_t* data, int* price_max);
  static void create_dataset(price_data_t** data, time_t time_now, int* price_max);
};
#pragma once

#include "U8g2lib.h"
#include <Wire.h>
#include "../dataset/dataset.h"

#define SCREEN_X_MIN 0
#define SCREEN_X_MAX 127
#define SCREEN_Y_MIN 0
#define SCREEN_Y_MAX 63

#define AXIS_X_MIN 10
#define AXIS_X_MAX 127
#define AXIS_Y_MIN 0
#define AXIS_Y_MAX (SCREEN_Y_MAX - 8)


class Chart {
public:
  // Functions
  static void init();
  static void draw(dataset_t* dataset);

  // MESSAGES
  static void write_init_message();
  static void write_hotspot_message(char* name, char* password, char* ip_address);

private:
  // Variables
  static U8G2_SH1106_128X64_NONAME_F_HW_I2C display;

  // Functions
  static int get_price_Y_max(int price_max);
  static char* int_to_label(int value);
  static void draw_XY_axis();
  static void draw_Y_labels(int price_y_max);
  static int get_Y_offset(int price_y_max, int price);
  static void draw_pillar_empty(int y_offset, int x_offset);
  static void draw_pillar_solid(int y_offset, int x_offset);
  static void draw_X_label(int hour, int x_offset);
  static void draw_pillars(dataset_t* dataset, int price_max);
  static void draw_Y_line_horizontal(int price_y_max);

  // MESSAGES
  static int get_X_offset_to_center_text(char* text);
};
#pragma once

#include "banner/banner.h"
#include "chart/chart.h"
#include "dataset/dataset.h"
#include "leds/leds.h"

#define GPIO_2   2
#define GPIO_13  13

#define PIN_BANNER  GPIO_13
#define PIN_CHART   GPIO_2

#define CHART_PILLARS_NUM 19


class Displays {
public:
  // Functions
  static void init();
  static void set_rgb_color(int red, int green, int blue);
  static void write_msg_starting();
  static void write_msg_hotspot(char* name, char* password, char* ip_address);
  static int draw(price_data_t* price_data, int time_now);

private:
  // Functions
  static void pin_high(int pin);
  static void pin_low(int pin);
  static void init_ctrl_pins();
  static void init_banner();
  static void init_chart();
  static void draw_banner(int price_now);
  static void draw_chart(dataset_t* dataset);
};

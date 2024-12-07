#pragma once

#include "banner/banner.h"
#include "chart/chart.h"
#include "dataset/dataset.h"
#include "leds/leds.h"

#define GPIO_0   0
#define GPIO_2   2

#define PIN_BANNER  GPIO_0  // D3
#define PIN_CHART   GPIO_2  // D4

#define CHART_PILLARS_NUM 19


class Displays {
public:
  // Functions
  static void init();
  static int draw(price_data_t* price_data, int time_now);
  static void chart_write_hotspot_messages(char* name, char* password, char* ip_address);

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

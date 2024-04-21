#pragma once

#include "networking/networking.h"
#include "banner/banner.h"
#include "chart/chart.h"

#define GPIO_14   14
#define GPIO_16   16

#define PIN_BANNER  GPIO_14
#define PIN_CHART   GPIO_16


class Displays {
public:
  // Functions
  static void init();
  static void draw(price_data_t** price_data, uint32_t time_now);

private:
  // Functions
  static void pin_high(int pin);
  static void pin_low(int pin);
  static void init_ctrl_pins();
  static void init_banner();
  static void init_chart();
  static void draw_banner(int price_now);
  static void draw_chart(price_data_t** price_data, uint32_t time_now);
};

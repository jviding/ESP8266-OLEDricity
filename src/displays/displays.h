#pragma once

#include "networking/networking.h"
#include "banner/banner.h"
#include "chart/chart.h"

#define GPIO_14   14
#define GPIO_16   16

#define PIN_BANNER  GPIO_14
#define PIN_CHART   GPIO_16

/*
* Displays share internal allocated memory.
* Requires re-init before each write, when displays are different size.
*/

class Displays {
public:
  // Functions
  static void init();
  static void draw(price_data_t** price_data, uint32_t time_now);

private:
  // Functions  
  static void draw_chart(price_data_t** price_data, uint32_t time_now);
  static void draw_banner(int price_now);
};

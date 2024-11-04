#pragma once

#include "banner/banner.h"
#include "chart/chart.h"
#include "dataset.h"

#define GPIO_14   14
#define GPIO_16   16

#define PIN_BANNER  GPIO_14
#define PIN_CHART   GPIO_16

#define CHART_PILLARS_NUM 19


class Displays {
public:
  // Functions
  static void init();
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

  // DATASET
  // Functions
  static bool set_ptr_to_data_now(dataset_t* dataset, price_data_t* data, int time_now);
  static void try_shift_data_ptr_one_left(dataset_t* dataset);
  static bool set_price_max(dataset_t* dataset, int dataset_size);
  static int create_dataset(dataset_t** dataset, price_data_t* data, int time_now);
};

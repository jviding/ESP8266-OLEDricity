#pragma once
#include <Arduino.h>

#define GPIO_12  12 // Red
#define GPIO_13  13 // Yellow
#define GPIO_15  15 // Green
#define GPIO_0   0  // Blue

#define LED_RED     GPIO_12
#define LED_YELLOW  GPIO_13
#define LED_GREEN   GPIO_15
#define LED_BLUE    GPIO_0


class Led {
public:
  // Functions
  static void init();

  static void blue();
  static void green();
  static void yellow();
  static void red();

private:
  // Functions
  static void set_all_low();
  static void set_one_high(uint8_t pin);
};

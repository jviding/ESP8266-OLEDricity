#pragma once
#include <Arduino.h>


#define GPIO_0   0
#define GPIO_13  13
#define GPIO_15  15

#define LED_RED     GPIO_0
#define LED_GREEN   GPIO_13
#define LED_BLUE    GPIO_15


class Leds {
public:
  // Functions
  static void init();

  static void run();
  static void shine(int red, int green, int blue);

private:
  // Functions
  static void set_all_low();
  static void to_high(int pin);
  static void to_low(int pin);
};

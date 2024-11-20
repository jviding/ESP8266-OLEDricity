#pragma once

#include <Arduino.h>


#define GPIO_0   0
#define GPIO_13  13
#define GPIO_15  15

#define LED_RED     GPIO_0
#define LED_GREEN   GPIO_13
#define LED_BLUE    GPIO_15

// RGB colors
// Min: 0
// Max: 255

// RGB(0,255,x) - Green is too dominant
// RGB(255,0,x) - Red is too dominant
// RGB(x,x,255) - Preferred shading


class Leds {
public:
  // Functions
  static void init();
  static void glow(int price);

private:
  // Functions
  static void set_rgb_color(int red, int green, int blue);
  static void glow_green_to_blue(int shade);
  static void glow_blue_to_red(int shade);
};

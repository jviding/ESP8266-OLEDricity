#pragma once

#include <Arduino.h>

#define GPIO_12  12
#define GPIO_14  14
#define GPIO_16  16

#define LED_BLUE    GPIO_12 // D6
#define LED_GREEN   GPIO_14 // D5
#define LED_RED     GPIO_16 // D0

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

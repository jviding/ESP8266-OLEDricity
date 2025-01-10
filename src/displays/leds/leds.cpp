#include "leds.h"


void Leds::init() {
  Serial.print("Leds: Initializing GPIO...");
  // Enable pins
  pinMode(LED_RED,    OUTPUT);
  pinMode(LED_GREEN,  OUTPUT);
  pinMode(LED_BLUE,   OUTPUT);
  delay(100);
  // Set all low
  digitalWrite(LED_RED,    LOW);
  digitalWrite(LED_GREEN,  LOW);
  digitalWrite(LED_BLUE,   LOW);  
  delay(100);
  // Done
  Serial.println("Ok.");
};

void Leds::set_rgb_color(int red, int green, int blue) {
  analogWrite(LED_RED,    red);
  analogWrite(LED_GREEN,  green);
  analogWrite(LED_BLUE,   blue);
};

void Leds::glow_green_to_blue(int shade) {
  if (shade <= 0) {
    set_rgb_color(0, 255, 0);   // Green
  } else if (shade <= 1) {
    set_rgb_color(0, 255, 100);
  } else if (shade <= 2) {
    set_rgb_color(0, 255, 200);
  } else if (shade <= 3) {
    set_rgb_color(0, 200, 255);
  } else {
    set_rgb_color(0, 100, 255);
  }
  /*else {
    int val = (255 / 5) * (5 - shade);
    set_rgb_color(0, val, 255);
  }*/
};

void Leds::glow_blue_to_red(int shade) {
  if (shade <= 0) {
    set_rgb_color(0, 0, 255);   // Blue
  } else if (shade <= 1) {
    set_rgb_color(100, 0, 255);
  } else if (shade <= 2) {
    set_rgb_color(200, 0, 255);
  } else if (shade <= 3) {
    set_rgb_color(255, 0, 200);
  } else {
    set_rgb_color(255, 0, 100);
  }
  /*else {
    int val = ((255 + 10) / 5) * shade;
    set_rgb_color(val, 0, 255);
  }*/
};

void Leds::glow(int price) {
  Serial.print("Leds: Adjusting RGB...");
  // Negative price is just green
  if (price < 0) price = 0;
  // Adjust color to price
  if (price < 10) {
    glow_green_to_blue(price / 2);
  } else if (price < 20) {
    glow_blue_to_red((price - 10) / 2);
  } else {
    set_rgb_color(255, 0, 0); // Red
  }
  Serial.println("Ok.");
};

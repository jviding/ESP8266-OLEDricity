#include "led.h"


void Led::init() {
  Serial.print("Initializing GPIO for Led...");
  pinMode(LED_BLUE,   OUTPUT);
  pinMode(LED_GREEN,  OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED,    OUTPUT);
  delay(100);
  set_all_low();
  Serial.print("Ok.");
};

void Led::set_all_low() {
  digitalWrite(LED_BLUE,   LOW);
  digitalWrite(LED_GREEN,  LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED,    LOW);
  delay(100);
};

void Led::set_one_high(uint8_t pin) {
  set_all_low();
  digitalWrite(pin, HIGH);
  delay(100);
};

void Led::blue() {
  set_one_high(LED_BLUE);
};

void Led::green() {
  set_one_high(LED_GREEN);
};

void Led::yellow() {
  set_one_high(LED_YELLOW);
};

void Led::red() {
  set_one_high(LED_RED);
};

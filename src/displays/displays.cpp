#include "displays.h"


void Displays::pin_high(int pin) {
  digitalWrite(pin, HIGH);
  delay(100);
};

void Displays::pin_low(int pin) {
  digitalWrite(pin, LOW);
  delay(100);
};

void Displays::init_ctrl_pins() {
  pinMode(PIN_BANNER, OUTPUT);
  pinMode(PIN_CHART,  OUTPUT);
  pin_low(PIN_BANNER);
  pin_low(PIN_CHART);
};

void Displays::init_banner() {
  pin_high(PIN_BANNER);
  Banner::init();
  pin_low(PIN_BANNER);
};

void Displays::init_chart() {
  pin_high(PIN_CHART);
  Chart::init();
  pin_low(PIN_CHART);
};

void Displays::init() {
  Serial.println("Initializing Displays...");
  init_ctrl_pins();
  Serial.println("Control pins ok.");
  init_banner();
  Serial.println("Banner display ok.");
  init_chart();
  Serial.println("Chart display ok.");
  Serial.println("Displays initialized.");
};

void Displays::draw_banner(int price_now) {
  pin_high(PIN_BANNER);
  Banner::draw(price_now);
  pin_low(PIN_BANNER);
};

void Displays::draw_chart(price_data_t** price_data, uint32_t time_now) {
  pin_high(PIN_CHART);
  Chart::draw(price_data, time_now);
  pin_low(PIN_CHART);
};

void Displays::draw(price_data_t** price_data, uint32_t time_now) {
  // Draw chart to calculate values and data_now
  draw_chart(price_data, time_now);
  // Read current price
  size_t index = Chart::data_now;
  int price = price_data[index]->cents_x100;
  // Draw price banner
  draw_banner(price);
};

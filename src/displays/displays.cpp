#include "displays.h"


void Displays::pin_high(int pin) {
  digitalWrite(pin, HIGH);
  delay(200);
};

void Displays::pin_low(int pin) {
  digitalWrite(pin, LOW);
  delay(200);
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
  delay(200);
  pin_low(PIN_BANNER);
};

void Displays::init_chart() {
  pin_high(PIN_CHART);
  Chart::init();
  delay(200);
  pin_low(PIN_CHART);
};

void Displays::init() {
  Serial.println("Displays: Initializing...");
  init_ctrl_pins();
  Serial.println("Displays: Control pins enabled.");
  Leds::init();
  init_banner();
  init_chart();
  Serial.println("Displays: Initialization ok.");
};

void Displays::set_rgb_color(int red, int green, int blue) {
  Leds::set_rgb_color(red, green, blue);
};

void Displays::write_msg_starting() {
  pin_high(PIN_BANNER);
  Banner::write_msg_brand();
  delay(200);
  pin_low(PIN_BANNER);
  pin_high(PIN_CHART);
  Chart::write_msg_starting();
  delay(200);
  pin_low(PIN_CHART);
};

void Displays::write_msg_hotspot(char* name, char* password, char* ip_address) {
  pin_high(PIN_BANNER);
  Banner::write_msg_brand();
  delay(200);
  pin_low(PIN_BANNER);
  pin_high(PIN_CHART);
  Chart::write_msg_hotspot(name, password, ip_address);
  delay(200);
  pin_low(PIN_CHART);
};

void Displays::draw_banner(int price_now) {
  pin_high(PIN_BANNER);
  Banner::draw(price_now);
  pin_low(PIN_BANNER);
};

void Displays::draw_chart(dataset_t* dataset) {
  pin_high(PIN_CHART);
  Chart::draw(dataset);
  pin_low(PIN_CHART);
};

int Displays::draw(price_data_t* price_data, int time_now) {
  Serial.println("Displays: Starting to draw...");
  dataset_t* dataset = new dataset_t;
  int res_ok = Dataset::create_dataset(&dataset, CHART_PILLARS_NUM, price_data, time_now);
  if (res_ok != 0) {
    Serial.println("Displays: Dataset ready.");
    // Draw
    draw_banner(dataset->price_now);
    draw_chart(dataset);
    Serial.println("Displays: Drawing ok.");
    // Leds
    Leds::glow(dataset->price_now / 100);
  } else {
    Serial.println("Displays: Failed creating dataset.");
  }
  delete dataset;
  return res_ok;
};

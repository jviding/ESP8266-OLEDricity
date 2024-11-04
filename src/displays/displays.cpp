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
  pin_low(PIN_BANNER);
};

void Displays::init_chart() {
  pin_high(PIN_CHART);
  Chart::init();
  pin_low(PIN_CHART);
};

void Displays::init() {
  Serial.println("Displays: Initializing...");
  init_ctrl_pins();
  Serial.println("Displays: Control pins ok.");
  init_banner();
  init_chart();
  Serial.println("Displays: Initialization ok.");
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
  int res_ok = 1;
  if ((res_ok = create_dataset(&dataset, price_data, time_now)) == 0) {
    Serial.println("Displays: Failed creating dataset.");
    return res_ok;
  }
  Serial.println("Displays: Dataset ready.");  
  // Draw
  draw_banner(dataset->price_now);
  draw_chart(dataset);
  // Free memory
  Serial.println("Displays: Drawing completed.");
  delete dataset;
  return true;
};

#include "displays.h"


void Displays::init() {
  Serial.print("Enabling Display control pins...");
  pinMode(PIN_BANNER, OUTPUT);
  pinMode(PIN_CHART,  OUTPUT);
  digitalWrite(PIN_BANNER, LOW);
  digitalWrite(PIN_CHART,  LOW);
  delay(100);
  Serial.println("Ok.");
};

void Displays::draw_banner(int price_now) {
  digitalWrite(PIN_BANNER, HIGH);
  delay(300);
  Banner::init();
  Banner::draw(price_now);
  digitalWrite(PIN_BANNER, LOW);
  delay(300);
};

void Displays::draw_chart(price_data_t** price_data, uint32_t time_now) {
  digitalWrite(PIN_CHART, HIGH);
  delay(300);
  Chart::init();
  Chart::draw(price_data, time_now);
  digitalWrite(PIN_CHART, LOW);
  delay(300);
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

#include "chart.h"


U8G2_SH1106_128X64_NONAME_F_HW_I2C Chart::display(U8G2_R0, U8X8_PIN_NONE);

int Chart::max_price;
price_data_t** Chart::data;


void Chart::init() {
  display.begin();  
};

void Chart::set_max_price() {
  max_price = 0;
  for (size_t i = 0; i < PRICE_MAX_LEN; i++) {
    if (max_price < data[i]->cents_x100) {
      max_price = data[i]->cents_x100;
    }
  }
  Serial.print("Max price: ");
  Serial.println(max_price);
  // Upper limit 99, notice x100
  if (max_price > 9900) {
    max_price = 9900;
    Serial.println("Exceeded limit, changed to 9900.");
  }
};

void Chart::draw_y_axis() {
  // Y axis top label
  char x10 = ((max_price / 100) / 10) + '0';
  char x1  = ((max_price / 100) % 10) + '0';
  char top[] = {x10, x1, '\0'};
  display.drawStr(0, 6, top);
  // Y axis bot label
  display.drawStr(0, Y_PLOT_MAX, " 0");
  // Y axis
  display.drawLine(10, 0, 10, Y_PLOT_MAX);
};

void Chart::draw_x_axis() {
  int x = 18;
  for (size_t i = 0; i < 5; i++) {
    int hour = data[i * 6 + 2]->hour;
    // Hour to string
    char x10 = (hour / 10) + '0';
    char x1  = (hour % 10) + '0';
    char h_str[] = {x10, x1, '\0'};
    // Draw
    display.drawStr(x, Y_MAX, h_str);
    // Move X cursor
    x += 24;
  }
  // X axis
  display.drawLine(10, Y_PLOT_MAX, X_MAX, Y_PLOT_MAX);
};

void Chart::draw_xy_mid() {
  // Y axis mid label
  char x10 = (((max_price / 2) / 100) / 10) + '0';
  char x1  = (((max_price / 2) / 100) % 10) + '0';
  char mid[] = {x10, x1, '\0'};
  // Y axis mid position
  // Adjust in case of rounded
  int y_height = ((((max_price / 2) * 100) / max_price) * Y_PLOT_MAX) / 100;
  int y = Y_PLOT_MAX - y_height;
  display.drawStr(0, y + 2, mid);
  // Draw along X axis
  display.drawLine(10, y, X_MAX, y);
};

void Chart::draw_pillar(int val, int x) {
  int y_height = (((val * 100) / max_price) * Y_PLOT_MAX) / 100;
  int y = Y_PLOT_MAX - y_height;
  display.drawBox(x, y, 2, y_height);
};

void Chart::draw_pillars() {
  int x = 14;
  for (size_t i = 0; i < 28; i++) {
    int val = data[i]->cents_x100;
    if (val > max_price) {
      val = max_price;
    }
    draw_pillar(val, x);
    x += 4;
  }
};

void Chart::draw() {
  data = Networking::price_data;
  display.clearBuffer();
  display.setFont(u8g2_font_5x7_tf);
  set_max_price();
  draw_y_axis();
  draw_x_axis();
  draw_xy_mid();
  draw_pillars();
  display.sendBuffer();
};

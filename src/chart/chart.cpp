#include "chart.h"


U8G2_SH1106_128X64_NONAME_F_HW_I2C Chart::display(U8G2_R0, U8X8_PIN_NONE);

int Chart::max_price;
price_data_t** Chart::data;
time_t Chart::time_now;
size_t Chart::data_now;
size_t Chart::data_from;
size_t Chart::data_to;

void Chart::init() {
  display.begin();  
};

void Chart::set_time_and_data_ptrs() {
  for (size_t i = 0; i < PRICES_MAX_NUM; i++) {
    bool now = true;
    now &= data[i]->year  == year(time_now);
    now &= data[i]->month == month(time_now);
    now &= data[i]->day   == day(time_now);
    now &= data[i]->hour  == hour(time_now);
    if (now) {
      data_now = i;
      data_from = i - 1;
      data_to = i - 1 + PILLARS_NUM;
      break;
    }
  }
};

void Chart::set_max_price() {
  max_price = 0;
  for (size_t i = data_from; i < data_to; i++) {
    if (max_price < data[i]->cents_x100) {
      max_price = data[i]->cents_x100;
    }
  }
  Serial.print("Max price: "); Serial.println(max_price);
  // Add +1 to distinguish between 'max prices'
  // It will be rounded, so f.ex. x.x, x.y, x.z would all show up as x
  max_price += 100;
  // Upper limit 99, notice x100
  // Lower limit 05
  if (max_price > 9900) {
    max_price = 9900;
    Serial.println("Max price exceeded limit, changed to 9900.");
  } else if (max_price < 500) {
    max_price = 500;
    Serial.println("Max price below limit, changed to 500.");
  }
};

char* Chart::get_int_as_label(int val) {
  // ASCII conversion
  char x10 = (val / 10) + '0';
  char x1  = (val % 10) + '0';
  return new char[3]{x10, x1, '\0'};
};

int Chart::get_pillar_height(int price) {
  // Avoid losing information with int rounded, int < 1 is 0
  return (((price * 100) / max_price) * Y_PLOT_MAX) / 100;
};

void Chart::draw_y_axis_mid() {
  // Y cursor
  int height = get_pillar_height(max_price / 2);
  int y = Y_PLOT_MAX - height;
  // Draw axis horizontal
  display.drawLine(10, y, X_CHART_MAX, y);
  // Draw mid label
  char* mid_label = get_int_as_label((max_price / 2) / 100);
  y += 2;
  display.drawStr(0, y, mid_label);
  delete[] mid_label;
};

void Chart::draw_axis() {
  // Draw top label
  char* top_label = get_int_as_label(max_price / 100);
  display.drawStr(0, 6, top_label);
  delete[] top_label;
  // Draw bottom label
  display.drawStr(0, Y_PLOT_MAX, " 0");
  // Draw Y axis
  display.drawLine(10, 0, 10, Y_PLOT_MAX);
  // Draw X axis
  display.drawLine(10, Y_PLOT_MAX, X_CHART_MAX, Y_PLOT_MAX);
  // Mid
  draw_y_axis_mid();
};

void Chart::draw_x_label(int hour, int x) {
  char* label = get_int_as_label(hour);
  display.drawStr(x, Y_CHART_MAX, label);
  delete[] label;
};

void Chart::draw_empty_pillar(int price, int x) {
  int height = get_pillar_height(price);
  int y = Y_PLOT_MAX - height;
  // Draw box
  display.drawLine(x, y, x + 3, y);
  display.drawLine(x, y, x, Y_PLOT_MAX);
  display.drawLine(x + 3, y, x + 3, Y_PLOT_MAX);
};

void Chart::draw_solid_pillar(int price, int x) {
  int height = get_pillar_height(price);
  int y = Y_PLOT_MAX - height;
  // Draw box
  display.drawBox(x, y, 4, height);
};

void Chart::draw_pillar(size_t index, int price, int x) {
  if (index == data_now) {
    draw_solid_pillar(price, x);
  } else {
    draw_empty_pillar(price, x);
  }
};

void Chart::draw_pillars() {
  int x = 14;
  int count = 0;
  for (size_t i = data_from; i < data_to; i++) {
    int price = data[i]->cents_x100;
    if (price > max_price) {
      // Notice the upper limit of 99 c/kWh
      price = max_price;
    }
    draw_pillar(i, price, x);
    // Draw label
    if ((count % 3) == 1) {
      draw_x_label(data[i]->hour, x - 3);
    }
    // Move X cursor and Counter
    x += 6;
    count++;
  }
};

void Chart::draw_init() {
  set_time_and_data_ptrs();
  set_max_price();
};

void Chart::draw(price_data_t** price_data, uint32_t current_time) {
  // Set data and time
  data = price_data;
  time_now = current_time;
  // Draw
  Serial.println("Initializing chart.");
  draw_init();
  Serial.print("Drawing...");
  display.clearBuffer();
  display.setFont(u8g2_font_5x7_tf);
  draw_axis();
  draw_pillars();
  display.sendBuffer();
  Serial.println("Done.");
};

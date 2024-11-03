#include "chart.h"

U8G2_SH1106_128X64_NONAME_F_HW_I2C Chart::display(U8G2_R0, U8X8_PIN_NONE);


void Chart::init() {
  Serial.print("Chart: Initializing...");
  display.begin();
  Serial.println("Ok.");
};

int Chart::get_price_Y_max(int price_max) {
  // Round up (+100) and convert to full cents (/100).
  // I.e., 12.20, 12.40, 12.60 wouldn't be drawn as just 12.
  int price_y_max = (price_max + 100) / 100;
  // Set limits in full cents, upper 99, lower 10
  price_y_max = price_y_max > 99 ? 99 : price_y_max;
  price_y_max = price_y_max < 10 ? 10 : price_y_max;
  return price_y_max;
};

// Value can have maximum two digits
char* Chart::int_to_label(int value) {
  // ASCII conversion
  char x10 = (value / 10) + '0';
  char x1  = (value % 10) + '0';
  return new char[3]{x10, x1, '\0'};
};

void Chart::draw_XY_axis() {
  display.drawLine(AXIS_X_MIN, AXIS_Y_MAX, AXIS_X_MAX, AXIS_Y_MAX); // X axis
  display.drawLine(AXIS_X_MIN, AXIS_Y_MIN, AXIS_X_MIN, AXIS_Y_MAX); // Y axis
};

void Chart::draw_Y_labels(int price_y_max) {
  // Top
  char* label = int_to_label(price_y_max);
  display.drawStr(0, 6, label);
  delete[] label;
  // Bottom
  display.drawStr(0, AXIS_Y_MAX, " 0");
};

int Chart::get_Y_offset(int price_y_max, int price) {
  // Convert back to price_x100 format
  price_y_max *= 100;
  // When value < value_max, then value / value_max < 1.
  // As integers < 1 are rounded to zero, result is always 0.
  // To avoid this issue, multiply x100 and later divide x100.
  return ((((price_y_max - price) * 100) / price_y_max) * AXIS_Y_MAX) / 100;
};

void Chart::draw_pillar_empty(int y_offset, int x_offset) {
  display.drawLine(x_offset, y_offset, x_offset + 3, y_offset);
  display.drawLine(x_offset, y_offset, x_offset, AXIS_Y_MAX);
  display.drawLine(x_offset + 3, y_offset, x_offset + 3, AXIS_Y_MAX);
};

void Chart::draw_pillar_solid(int y_offset, int x_offset) {
  display.drawBox(x_offset, y_offset, 4, AXIS_Y_MAX - y_offset);
};

void Chart::draw_X_label(int hour, int x_offset) {
  char* label = int_to_label(hour);
  display.drawStr(x_offset, SCREEN_Y_MAX, label);
  delete[] label;
};

void Chart::draw_pillars(dataset_t* dataset, int price_y_max) {
  price_data_t* temp = dataset->price_data;
  for (int i = 0; i < dataset->size; i++) {
    // Get price
    int price = temp->cents_x100;
    price = price > 9900 ? 9900 : price;  // Upper limit 99.00
    price = price < 0 ? 0 : price;        // Lower limit 0
    // Draw pillar
    int x_offset = 14 + (i * 6);
    int y_offset = get_Y_offset(price_y_max, price);
    if (temp->time == dataset->time_now) {
      draw_pillar_solid(y_offset, x_offset);
    } else {
      draw_pillar_empty(y_offset, x_offset);
    }
    // Draw X label
    if (i % 3 == 1) {
      int hour = temp->time % 100;
      draw_X_label(hour, x_offset - 3);
    }
    // Next
    temp = temp->next;
  }
};

void Chart::draw_Y_line_horizontal(int price_y_max) {
  int y_mid = price_y_max / 2;
  // Draw line
  int y_offset = get_Y_offset(price_y_max, y_mid * 100);
  display.drawLine(AXIS_X_MIN, y_offset, AXIS_X_MAX, y_offset);
  // Draw label
  char* label = int_to_label(y_mid);
  display.drawStr(0, y_offset + 3, label);
  delete[] label;
};

void Chart::draw(dataset_t* dataset) {
  Serial.print("Chart: Drawing...");
  // Price max to correct format
  int price_y_max = get_price_Y_max(dataset->price_max);
  // Draw
  display.clearBuffer();
  display.setFont(u8g2_font_5x7_tf);
  draw_XY_axis();
  draw_Y_labels(price_y_max);
  draw_pillars(dataset, price_y_max);
  draw_Y_line_horizontal(price_y_max);
  display.sendBuffer();
  Serial.println("Ok.");
};

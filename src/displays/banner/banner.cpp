#include "banner.h"

U8G2_SH1106_128X32_VISIONOX_F_HW_I2C Banner::display(U8G2_R0, U8X8_PIN_NONE);


void Banner::init() {
  Serial.print("Banner: Initializing...");
  display.begin();
  Serial.println("Ok.");
};

void Banner::power_up() {
  display.setPowerSave(0);
  Serial.println("Banner: Power up.");
};

void Banner::power_down() {
  display.setPowerSave(1);
  Serial.println("Banner: Power down.");
};

int Banner::get_price_x100_num_of_digits_in_full_cents(int price_x100) {
  int counter = 1;
  price_x100 /= 100;
  while ((price_x100 /= 10) != 0) counter++;
  return counter;
};

int Banner::get_price_x100_num_of_digits_in_decimals(int price_x100) {
  bool has_two = price_x100 % 10 != 0;   // 0.0X
  if (has_two) return 2;
  bool has_one = price_x100 % 100 != 0;  // 0.X-
  if (has_one) return 1;
  return 0;                              // 0.--
};

char Banner::int_to_char(int val) {
  // ASCII conversion
  return val + '0';
};

void Banner::price_x100_to_str(char** str, int price_x100) {
  bool is_neg = price_x100 < 0;
  if (is_neg) price_x100 *= -1;
  int num_full = get_price_x100_num_of_digits_in_full_cents(price_x100);
  int num_dec = get_price_x100_num_of_digits_in_decimals(price_x100);
  // +1 for '.', +1 for '-', +1 for '\0'
  int num_chars = num_full + num_dec + (num_dec > 0 ? 1 : 0) + (is_neg ? 1 : 0) + 1;
  // Allocate space
  *str = new char[num_chars];
  (*str)[num_chars - 1] = '\0';
  (*str)[0] = '-';
  // Drop trailing zeros from decimal part
  for (int i = 0; i < 2 - num_dec; i++) price_x100 /= 10;
  // Read price to str
  for (int i = num_chars - 2; i >= (is_neg ? 1 : 0); i--) {
    if (num_dec > 0 && i == num_chars - 2 - num_dec) {
      (*str)[i] = '.';
    } else {
      (*str)[i] = int_to_char(price_x100 % 10);
      price_x100 /= 10;
    }
  }
};

void Banner::draw_price(int price_x100) {
  char* str = nullptr;
  price_x100_to_str(&str, price_x100);
  // Get XY positions
  int x_offset = (X_BANNER_MAX / 2) - (display.getUTF8Width(str) / 2);
  int y_offset = Y_BANNER_MAX - 2;
  // Draw
  display.drawStr(x_offset, y_offset, str);
  // Release
  delete[] str;
};

void Banner::draw(int price_x100) {
  Serial.print("Banner: Drawing...");
  // Rotate 180 because display is installed upside down
  display.setDisplayRotation(U8G2_R2);
  display.clearBuffer();
  display.setFont(u8g2_font_fub25_tn); // width: 27, height: 31
  draw_price(price_x100);
  display.sendBuffer();
  Serial.println("Ok.");
};

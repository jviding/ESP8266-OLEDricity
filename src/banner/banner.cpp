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

int Banner::get_num_of_digits(int val) {
  if (val == 0) return 1;
  // Calculate
  int num = 0;
  while ((val /= 10) != 0) num++;
  return num;
};

char Banner::get_int_as_char(int val) {
  // ASCII conversion
  return val + '0';
};

// Takes only positive values
char* Banner::get_int_as_str(int val) {
  int len = get_num_of_digits(val);
  char* str = new char[len + 2];
  str[len + 1] = '\0';
  for (int i = len; i >= 0; i--) {
    if (i == len - 2) {
      str[i] = '.';
    } else {
      str[i] = get_int_as_char(val % 10);
      val /= 10;
    }
  }  
  return str;
};

void Banner::draw_price(int price_x100) {
  int num_digits = get_num_of_digits(price_x100);
  char* price_str = get_int_as_str(price_x100);
  // Get XY positions
  int x = (X_BANNER_MAX / 2) - (9 * num_digits) - 5;
  int y = Y_BANNER_MAX - 2;
  // Draw
  display.drawStr(x, y, price_str);
  // Release memory
  delete[] price_str;
};

void Banner::draw(int price_x100) {
  Serial.print("Banner: Drawing...");
  // No negative
  if (price_x100 < 0) {
    price_x100 = 0;
  }
  // Rotate 180 because display is installed upside down
  display.setDisplayRotation(U8G2_R2);
  // Draw
  display.clearBuffer();
  display.setFont(u8g2_font_fub25_tr); // width: 35, height: 37
  draw_price(price_x100);
  display.sendBuffer();
  Serial.println("OK.");
};

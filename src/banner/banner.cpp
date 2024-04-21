#include "banner.h"

U8G2_SH1106_128X32_VISIONOX_F_HW_I2C Banner::display(U8G2_R0, U8X8_PIN_NONE);


void Banner::init() {
  Serial.print("Initializing Banner display...");
  display.begin();
  Serial.println("Ok.");
};

void Banner::power_up() {
  display.setPowerSave(0);
  Serial.println("Banner - power up.");
};

void Banner::power_down() {
  display.setPowerSave(1);
  Serial.println("Banner - power down.");
};

int Banner::get_num_of_digits(int val) {
  if (val == 0) {
    return 1;
  }
  // Use positive to calculate
  if (val < 0) {
    val *= -1;
  }
  // Calculate
  int num = 0;
  while (val > 0) {
    val /= 10;
    num++;
  }
  return num;
};

char Banner::get_int_as_char(int val) {
  // ASCII conversion
  return val + '0';
};

// Takes only positive values
char* Banner::get_int_as_str(int val, int len) {
  char* str = new char[len + 2];
  // Write int
  for (int i = len; i >= 0; i--) {
    if (i == len - 2) {
      str[i] = '.';
    } else {
      int to_char = val % 10;
      val = val / 10;
      str[i] = get_int_as_char(to_char);
    }
  }
  // Add EOF
  str[len + 1] = '\0';
  return str;
};

void Banner::draw_price(int price_x100) {
  // Get length
  int num_digits = get_num_of_digits(price_x100);
  // Convert to string
  char* price_str = get_int_as_str(price_x100, num_digits);
  // Get XY positions
  int x = (X_BANNER_MAX / 2) - (9 * num_digits) - 5;
  int y = Y_BANNER_MAX - 2;
  // Draw
  display.drawStr(x, y, price_str);
  // Release memory
  delete price_str;
};

void Banner::draw(int price_x100) {
  Serial.print("Drawing Banner...");
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
  Serial.println("Ok.");
};

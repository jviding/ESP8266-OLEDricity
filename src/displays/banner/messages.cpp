#include "banner.h"


int Banner::get_X_offset_to_center_text(char* text) {
  return (X_BANNER_MAX - display.getUTF8Width(text)) / 2;
};

void Banner::write_brand_message() {
  Serial.print("Banner: Writing brand...");
  // Prepare
  display.setDisplayRotation(U8G2_R2);
  display.clearBuffer();
  display.setFont(u8g2_font_helvB08_tf);
  // Add message
  char* msg = strdup("Jasu Viding tmi");
  int x_offset = get_X_offset_to_center_text(msg);
  display.drawStr(x_offset, 15, "Powered by:");
  display.drawStr(x_offset, 30, "Jasu Viding tmi");
  // Write
  display.sendBuffer();
  Serial.println("Ok.");
  delete[] msg;
};

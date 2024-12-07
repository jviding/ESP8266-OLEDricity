#include "chart.h"

int Chart::get_X_offset_to_center_text(char* text) {
  return (SCREEN_X_MAX - display.getUTF8Width(text)) / 2;
};

void Chart::write_init_message() {
  Serial.print("Chart: Writing init msg...");
  // Prepare
  display.clearBuffer();
  display.setFont(u8g2_font_helvB08_tf);
  // Add message
  int x_offset = 5;
  display.drawStr(x_offset, 12, "Starting...");
  // Write
  display.sendBuffer();
  Serial.println("Ok.");
};

void Chart::write_hotspot_message(char* name, char* password, char* ip_address) {
  Serial.print("Chart: Writing hotspot msg...");
  // Prepare
  display.clearBuffer();
  display.setFont(u8g2_font_helvB08_tf);
  // Add message
  int x_offset = 5;
  display.drawStr(x_offset, 12, "Join the HotSpot");
  display.drawStr(x_offset, 24, ((String)"SSID: " + name).c_str());
  display.drawStr(x_offset, 36, ((String)"Passwd: " + password).c_str());
  display.drawStr(x_offset, 51, "Then set WiFi details");
  display.drawStr(x_offset, 63, ((String)"http://" + ip_address).c_str());
  // Write
  display.sendBuffer();
  Serial.println("Ok.");
};

#include "displays_test.h"


void Displays_test::test_displays_with_data_fast_loop() {
  bool res_ok;
  // Get time
  int time_now = 0;
  res_ok = Networking::get_time(&time_now);
  // Get data
  price_data_t* data = nullptr;
  res_ok &= Networking::get_data(&data);
  // Loop until no data to display
  while (res_ok) {
    // Draw
    res_ok &= Displays::draw(data, time_now) != 0;
    // Next hour
    if (time_now % 100 == 23) {
      time_now += 100 - 23;
    } else {
      time_now++;
    }
    // Wait
    delay(200);
  }
  // Clear memory
  while (data != nullptr) {
    price_data_t* temp = data->next;
    delete data;
    data = temp;
  }
};

bool Displays_test::enable_networking_for_real_data() {
  char* ip_address = nullptr;
  char* password = nullptr;
  bool res_ok = true;
  if (!Networking::enable()) {
    Serial.println("## Test Displays: Set WiFi credentials.");
    res_ok = Networking::hotspot_enable(&ip_address, &password);
    res_ok = res_ok && Networking::set_WiFi_SSID_and_password();
    res_ok = res_ok && Networking::hotspot_disable();
  }
  delete[] ip_address;
  delete[] password;
  if (!res_ok) {
    Serial.println("## Test Displays: Failed enabling real data use");
    delay(500);
  }
  return res_ok;
};

void Displays_test::test_chart_write_hotspot_ip_and_pwd() {
  Chart_test::test_write_hotspot_ip_and_pwd();
};

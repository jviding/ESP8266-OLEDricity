#include "Arduino.h"
#include "networking/networking.h"
#include "displays/displays.h"

//#include "tests/tests.h"


void start_serial() {
  Serial.begin(115200);
  while (!Serial) {
    ; // Wait until serial port connected
  }
  delay(100);
  Serial.println("Main: Serial started.");
};

void reset_wifi_credentials_and_connect() {
  char* password = nullptr;
  char* ip_address = nullptr;
  while (true) {
    // Enable HotSpot
    Networking::hotspot_enable(CONFIG_HOTSPOT_NAME, &password, &ip_address);
    Displays::write_msg_hotspot(CONFIG_HOTSPOT_NAME, password, ip_address);
    // Set WiFi credentials
    Networking::set_WiFi_SSID_and_password();
    // Disable HotSpot
    Networking::hotspot_disable();
    // Try WiFi connection
    Displays::write_msg_starting();
    Displays::set_rgb_color(0, 0, 255); // Blue
    if (Networking::connect()) {
      break;
    } else {
      Displays::set_rgb_color(255, 0, 0); // Red
    }
  }
  delete[] password;
  delete[] ip_address;
};

void start_wifi() {
  bool wifi_ok = Networking::enable() && Networking::connect();
  if (!wifi_ok) {
    reset_wifi_credentials_and_connect();
  }
  Displays::set_rgb_color(0, 255, 0); // Green
};

void setup() {
  start_serial();
  // TEST
  //Tests::test();
  // PRODUCTION
  Displays::init();
  Displays::set_rgb_color(0, 0, 255); // Blue
  Displays::write_msg_starting();
  start_wifi();
};

void handle_errors(int code) {
  Serial.print("Main: Error code: ");
  Serial.println(code);
};

void loop() {
  // Time & Data
  int time_now = 0;
  price_data_t* data = nullptr;
  // Get data
  if (!Networking::get_data(&data)) {
    Serial.println("Main: Get data failed.");
    handle_errors(2);
    return;
  }
  // Loop until data EOF
  while (true) {
    // Get time
    if (!Networking::get_time(&time_now)) {
      Serial.println("Main: Get time failed.");
      handle_errors(1);
      break;
    }
    // Draw
    int res_code = Displays::draw(data, time_now);
    if (res_code == 0) {
      Serial.println("Main: No data for time now.");
      break;
    }
    // Wait until hour changed
    Networking::wait_until_hour_changed(time_now);
    // If EOF, break to get new data
    if (res_code == 2) {
      Serial.println("Main: Data EOF, reload.");
      break;
    }
  }
  // Free all memory
  while (data != nullptr) {
    price_data_t* temp = data->next;
    delete data;
    data = temp; 
  }
};

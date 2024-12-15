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

bool reset_wifi_credentials() {
  // Enable HotSpot
  char* password = nullptr;
  char* ip_address = nullptr;
  Networking::hotspot_enable(CONFIG_HOTSPOT_NAME, &password, &ip_address);
  Displays::chart_write_hotspot_messages(CONFIG_HOTSPOT_NAME, password, ip_address);
  delete[] password;
  delete[] ip_address;
  // Set WiFi credentials
  Networking::set_WiFi_SSID_and_password();
  // Disable HotSpot
  Networking::hotspot_disable();
  return true;
};

void setup() {
  start_serial();
  // TEST
  //Tests::test();
  // PRODUCTION
  Displays::init();
  if (!Networking::enable() && !Networking::connect()) { 
    // TODO: Add Button press to reset?
    reset_wifi_credentials();
  }
  // TODO: Show errors on displays? Error codes or text?
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

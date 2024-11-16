#include "Arduino.h"
#include "networking/networking.h"
#include "displays/displays.h"
#include "leds/leds.h"
//#include "time.h"

#include "tests/tests.h"

 /* 
  * IDEAS
  * - Show price Now and Day Average?
  * - Follow actual price with mid line?
  * - Use set address, and remove mosfets?
  * 
  * BUG/FIX
  * - Pull-ups to display sclk
  * 
  * 
  */

// Allow WiFi without password!

// Show negative price on Banner

// Show error codes on display?
// F.ex. create class Error, to store/read
// Would help debugging exceptions
// WiFi can freeze - add timeout and retry? (show error?)


void start_serial() {
  Serial.begin(115200);
  while (!Serial) {
    ; // Wait until serial port connected
  }
  delay(100);
  Serial.println("Main: Serial started.");
};

bool set_wifi_credentials() {
  // Enable HotSpot
  char* ip_address = nullptr;
  char* password = nullptr;
  Networking::hotspot_enable(&ip_address, &password);
  delete[] ip_address;
  delete[] password;

  // Test these
  Serial.println("MAIN: Write IP & PWD to display");
  Serial.print(" - IP: "); Serial.println(ip_address);
  Serial.print(" - PWD: "); Serial.println(password);

  // Set WiFi credentials
  Networking::set_WiFi_SSID_and_password();
  // Disable HotSpot
  Networking::hotspot_disable();

  // Return error & show on display
  return true;
};

void setup() {
  start_serial();
  // TEST
  Tests::test();
  // PRODUCTION
  //Led::init();
  Displays::init();
  if (!Networking::enable()) { // BUTTON PRESS FOR RESET
    set_wifi_credentials();
  }

  // Show errors on displays?
  // Codes or text?

};

void loop() {
  
  //Led::run();

  //delay(1000);

  // LEDS
  /*delay(500);
  Led::blue();
  delay(500);
  Led::green();
  delay(500);
  Led::yellow();
  delay(500);
  Led::red();*/

  // Wait 1h -> Draw next hour
  // Wait 12h -> new data
  // Function to compute delay?
  // Return 1/2 of time until hour change?
  // Avoid too small values, set limits

  // Disconnect after data, to free memory for PWM

  // New data only when prev ends!
 
  // Then disconnect WiFI for 12h or so
  // If this fails, retry and x2 the wait if fails
  // Show error on screen?

};

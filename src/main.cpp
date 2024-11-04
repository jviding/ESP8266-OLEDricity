#include "Arduino.h"
#include "networking/networking.h"
#include "displays/displays.h"
//#include "led/led.h"
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

void setup() {
  start_serial();
  //Led::init();
  Displays::init();
  Networking::enable();
};

void loop() {

  bool res_ok = true;

  // Get time
  int time_now = 0;
  res_ok &= Networking::get_time(&time_now);
  // Get data
  price_data_t* data = nullptr;
  res_ok &= Networking::get_data(&data);
 
  while (res_ok) {
    // Draw
    res_ok = Displays::draw(data, time_now) == 1;
    // Wait until hour changes
    //time_now = new_time

    if (time_now % 23 == 0) {
      time_now += 100;
      time_now /= 100;
    } else {
      time_now++;
    }

    if (res_ok != 0) {
      res_ok = true;
    }

    delay(2000);
  }

  // TESTS
  //Tests::print_time(time_now);
  //Tests::print_price_data(data);
  Tests::debug_print_heap();

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

  // New data only when prev ends!
 
  // Then disconnect WiFI for 12h or so
  // If this fails, retry and x2 the wait if fails
  // Show error on screen?

  while (data != nullptr) {
    price_data_t* temp = data->next;
    delete data;
    data = temp;
  }

  delay(2000);
};

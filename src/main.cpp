#include "Arduino.h"
#include "networking/networking.h"
#include "displays/displays.h"
//#include "led/led.h"
//#include "time.h"

 /* 
  * IDEAS
  * - Show price Now and Day Average?
  * - Follow actual price with mid line?
  * - Pull-down to display sclk?
  */

  // Use set address?
  // Fixes problems with Mosfet?

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
  //Chart::init();
  //Led::init();
  //Displays::init();
  Networking::enable();
};

void debug_print_heap() {
  uint32_t free = ESP.getFreeHeap();
  Serial.print("Free heap: ");
  Serial.println(free);
};

void loop() {
  bool res_ok = true;
  // Get time
  time_t time_now;
  res_ok &= Networking::get_time(&time_now);
  // Get data
  price_data_t* data;
  res_ok &= Networking::get_data(&data);

  // Test
  Serial.print("Main: Time is now "); Serial.println(time_now);

  Serial.print("\n Main: Price Data");
  int counter = 1;
  while (data != nullptr) {
    // Print
    Serial.print(" -"); Serial.print(counter); Serial.print(": ");
    Serial.print("Time: "); Serial.print(data->time);
    Serial.print(" Price: "); Serial.print(data->cents_x100 / 100); Serial.print("."); Serial.println(data->cents_x100 % 100);
    // Delete
    price_data_t* temp = data->next;
    delete data;
    data = temp;
    // Counter
    counter++;
  }
  Serial.print("\n\n");


  delay(5000);


  //Chart::draw();
  // Draw to displays
  //Displays::draw(price_data, time_now);


  // Leds

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
 
  // Then disconnect WiFI for 12h or so
  // If this fails, retry and x2 the wait if fails
  // Show error on screen?

};

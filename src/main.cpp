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


// CHECK HOW TO DELETE OBJECT, INSTEAD OF POINTER
// obj_t { *ptr }
// if call "delete ptr" will it remove it?


// Somewhere is leaking memory???



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
  //Networking::update_data();
  //Chart::draw();
  // Update prices and time
  //Networking::update_data();
  //price_data_t** price_data = Networking::price_data;
  //uint32_t time_now = Networking::get_time();
  // Draw to displays
  //Displays::draw(price_data, time_now);

  delay(5000);

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
 
  /*Serial.print("Time: "); 
  Serial.print(year(time_now));
  Serial.print("-");
  Serial.print(month(time_now));
  Serial.print("-");
  Serial.print(day(time_now));
  Serial.print("-T");
  Serial.print(hour(time_now));
  Serial.println("");*/

  Serial.println("Hello");

  // Then disconnect WiFI for 12h or so
  // If this fails, retry and x2 the wait if fails
  // Show error on screen?

  delay(2000);

  time_t time_now;
  Networking::get_time(&time_now);
  Serial.print("Main: Time now: ");
  Serial.println(time_now);

  delay(2000);

  price_data_t* data;
  Networking::get_data(&data);

  Serial.print("\n\n");
  price_data_t* temp;
  while (data != nullptr) {
    // Print
    Serial.print("Time: "); Serial.print(data->time);
    Serial.print(" Price: "); Serial.println(data->cents_x100);
    // Delete
    temp = data->next;
    delete data;
    data = temp;
  }
  Serial.print("\n\n");

};

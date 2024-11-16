#include "Arduino.h"
#include "networking/networking.h"
#include "displays/displays.h"
#include "led/led.h"
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

  Tests::test();

  //Led::init();
  //Displays::init();
  //Networking::enable();
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

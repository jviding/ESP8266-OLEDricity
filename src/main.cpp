#include "Arduino.h"
#include "networking/networking.h"
#include "chart/chart.h"

#include "time.h"

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
  Serial.println("Started Serial.");
};

void setup() {
  start_serial();
  Chart::init();
  Networking::enable();
};

void loop() {  
  Networking::update_data();
  Chart::draw();

  delay(2000);

  uint32_t free = ESP.getFreeHeap();
  Serial.print("Free heap: ");
  Serial.println(free);

  // Then disconnect WiFI for 12h or so
  // If this fails, retry and x2 the wait if fails
  // Show error on screen?

  delay(2000);
};

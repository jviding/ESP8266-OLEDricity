#include "Arduino.h"
#include "networking/networking.h"
#include "chart/chart.h"


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

  Serial.println("Data");
  delay(1000);

  //price_data_t** data = Networking::price_data;
  /*for (size_t i = 0; i < PRICES_MAX_NUM; i++) {
    //Serial.println(i);
    //Serial.print(" - Price: "); Serial.println(data[i]->cents_x100);
    //Serial.print(" - Time: ");  Serial.println(data[i]->hour);
    Serial.print(data[i]->year);
    Serial.print(data[i]->month); 
    Serial.print(data[i]->day);
    Serial.print(data[i]->hour); 
    Serial.println("");
    delay(100);
  }*/

  Serial.println("Done.\n");

  uint32_t free = ESP.getFreeHeap();
  Serial.print("Free heap: ");
  Serial.println(free);

  //OLED::displayText();


  // Then disconnect for 12h or so
  // If this fails, retry and x2 the wait if fails
  // Show error on screen?


  delay(1000);
};

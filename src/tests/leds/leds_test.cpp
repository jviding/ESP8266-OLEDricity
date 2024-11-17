#include "leds_test.h"


void Leds_test::run_colors() {
  Serial.println("## Test Leds: Run colors through");

  // Start Green
  Serial.println("GREEN");
  Leds::shine(0,255,0);
  delay(2000);

  // Green to Blue
  Leds::shine(0,255,128);
  Serial.println("GREEN - b");
  delay(2000);
  Leds::shine(0,255,255);
  Serial.println("GREEN - B");
  delay(2000);
  Leds::shine(0,128,255);
  Serial.println("BLUE - g");
  delay(2000);
  Leds::shine(0,0,255);
  Serial.println("BLUE");
  delay(2000);

  // Blue to Red
  Leds::shine(128,0,255);
  Serial.println("BLUE - r");
  delay(2000);
  Leds::shine(255,0,255);
  Serial.println("BLUE - R");
  delay(2000);
  Leds::shine(255,0,128);
  Serial.println("RED - b");
  delay(2000);
  Leds::shine(255,0,0);
  Serial.println("RED");
  delay(2000);

  // Red to Green
  Leds::shine(255,128,0);
  Serial.println("RED - g");
  delay(2000);
  Leds::shine(255,255,0);
  Serial.println("RED - G");
  delay(2000);
  Leds::shine(128,255,0);
  Serial.println("GREEN - r");
  delay(2000);

};

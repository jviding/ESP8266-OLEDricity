#include "leds.h"


// analogWrite(pin, value);
// Val 255 = 1
// Val 0   = 0

void Leds::init() {
  Serial.print("Initializing GPIO for Led...");
  // Enable
  pinMode(LED_BLUE,   OUTPUT);
  pinMode(LED_GREEN,  OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED,    OUTPUT);
  // Default Low

  delay(100);
  set_all_low();
  Serial.print("Ok.");
};

void Leds::set_all_low() {
  digitalWrite(LED_BLUE,   LOW);
  digitalWrite(LED_GREEN,  LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED,    LOW);
  delay(100);
};

void Leds::set_one_high(uint8_t pin) {
  set_all_low();
  digitalWrite(pin, HIGH);
  delay(100);
};

void Leds::blue() {
  set_one_high(LED_BLUE);
};

void Leds::green() {
  set_one_high(LED_GREEN);
};

void Leds::yellow() {
  set_one_high(LED_YELLOW);
};

void Leds::red() {
  set_one_high(LED_RED);
};

void Leds::to_high(int pin) {
  for (int i = 0; i <= 255; i++) {
    analogWrite(pin, i);
    delay(10);
  }
};

void Leds::to_low(int pin) {
  for (int i = 255; i >= 0; i--) {
    analogWrite(pin, i);
    delay(10);
  }
};

void Leds::shine(int red, int green, int blue) {
  analogWrite(LED_RED, red);
  analogWrite(LED_GREEN, green);
  analogWrite(LED_YELLOW, blue);
  //delay(1000);
};

void Leds::run() {

    // Find orange
    shine(0, 255, 0);
    for (int i = 0; i <= 255; i++) {
      shine(i, 255, 0);
      delay(50);
    }

    /*// Start Green
    shine(0, 255, 0);

    // Green to Blue
    to_high(LED_YELLOW);
    to_low(LED_GREEN);
    // Blue to Red
    to_high(LED_RED);
    to_low(LED_YELLOW);
    // Red to Green
    to_high(LED_GREEN);
    to_low(LED_RED);

    Serial.println("Now GREEN");

    delay(1000);

    shine(0, 0, 0);
    to_high(LED_YELLOW); // Blue
    to_high(LED_GREEN);  // Green
    to_high(LED_RED); // Red

    Serial.println("Now WHITE");

    delay(1000);

    shine(255, 255, 255);

    Serial.println("Now Manual WHITE");

    delay(1000);*/

    /*// Blue to Green
    shine(0, 0, 255);
    shine(0, 128, 255);
    shine(0, 255, 255);
    shine(0, 255, 128);
    // Green to Red
    shine(0, 255, 0);
    shine(128, 255, 0);
    shine(255, 255, 0);
    shine(255, 128, 0);
    // Red to Blue
    shine(255, 0, 0);
    shine(255, 0, 128);
    shine(255, 0, 255);
    shine(128, 0, 255);*/


  /*for (int position = 0; position < 6; position++) {

    int x = 0;

    int red = 0;
    int green = 0;
    int blue = 0;

    for (int i = 0; i <= 255; i++) {

      x = i;

      if (position < 1) {         // Red to Yellow
        red = 255; green = x; blue = 0;
      } else if (position < 2) {  // Yellow to Green
        red = x; green = 255; blue = 0;
      } else if (position < 3) {  // Green to Cyan
        red = 0; green = 255; blue = x;
      } else if (position < 4) {  // Cyan to Blue
        red = 0; green = x; blue = 255;
      } else if (position < 5) {  // Blue to Magenta
        red = x; green = 0; blue = 255;
      } else {                    // Magenta to Red
        red = 255; green = 0; blue = x;
      }

      analogWrite(LED_RED, red);
      analogWrite(LED_GREEN, green);
      analogWrite(LED_YELLOW, blue);
      delay(10);
    }

    Serial.print("R:"); Serial.print(red); Serial.print(" G:"); Serial.print(green); Serial.print(" B:"); Serial.println(blue); 

    delay(500);

  }*/


};

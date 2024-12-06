#include "leds_test.h"


void Leds_test::test_rgb() {
  Serial.println("## Test Leds: Run colors through");
  for (int i = 1; i < 22; i += 2) {
    Leds::glow(i);
    delay(500);
  }
};

#include "chart_test.h"

void Chart_test::test_write_hotspot_message() {
  Serial.println("## Test Display Chart: Write HotSpot IP and Password");
  char* name = new char[12]{'E','l','e','c','t','r','i','c','u','b','e','\0'};
  char* pwd = new char[9]{'8','8','8','8','8','8','8','8','\0'};
  char* ip = new char[16]{'2','5','5','.','2','5','5','.','2','5','5','.','2','5','5','\0'};
  Displays::write_msg_hotspot(name, pwd, ip);
  delete[] name;
  delete[] pwd;
  delete[] ip;
  Serial.println("## Test Display Chart: Written");
  Serial.println("## Test Display Chart: COMPLETED");
  delay(500);
};

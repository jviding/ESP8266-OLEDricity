#include "eeprom_test.h"


bool Eeprom_test::try_read() {
  char* ssid = nullptr;
  char* pwd = nullptr;
  bool res_ok = Eeprom_ctrl::read_SSID_and_password(&ssid, &pwd);
  if (res_ok) {
    Serial.println("Try read - Succeeded");
    Serial.print(" - SSID: "); Serial.println(ssid);
    Serial.print(" - Password: "); Serial.println(pwd);
  } else {
    Serial.println("Try read - Failed");
  }
  delete[] ssid;
  delete[] pwd;
  return res_ok;
};

bool Eeprom_test::try_write() {
  char* ssid = new char[4]{'a', 's', 'd', '\0'};
  char* pwd = new char[4]{'1', '2', '3', '\0'};
  bool res_ok = Eeprom_ctrl::write_SSID_and_password(ssid, pwd);
  if (res_ok) {
    Serial.println("Try write - Succeeded");
    Serial.print(" - SSID: "); Serial.println(ssid);
    Serial.print(" - Password: "); Serial.println(pwd);
  } else {
    Serial.println("Try write - Failed");
  }
  delete[] ssid;
  delete[] pwd;
  return res_ok;
};

bool Eeprom_test::print_result(bool res_ok, int num_test) {
  Serial.print("Test "); Serial.print(num_test); Serial.print(": ");
  Serial.println(res_ok ? "SUCCEEDED" : "FAILED");
  return res_ok;
};

void Eeprom_test::test() {
  Serial.println("\n** EEPROM TESTS **\n");
  // 1. Clear SSID and Password
  Serial.println("Test: Clearing SSID and Password.");
  Eeprom_ctrl::clear_SSID_and_password();
  delay(200);
  // 2. Try read (should fail)
  bool res_1 = !try_read();
  delay(200);
  // 3. Try write (should succeed)
  bool res_2 = try_write();
  delay(200);
  // 4. Try read (should succeed)
  bool res_3 = try_read();
  delay(200);
  // 5. Clear SSID and Password
  Serial.println("Test: Clearing SSID and Password.");
  Eeprom_ctrl::clear_SSID_and_password();
  delay(200);
  // 6. Try read (should fail)
  bool res_4 = !try_read();
  delay(200);
  // Done
  Serial.println("\n** EEPROM TESTS COMPLETED **\n");
  print_result(res_1, 1);
  print_result(res_2, 2);
  print_result(res_3, 3);
  print_result(res_4, 4);
  Serial.println("\n");
  delay(1000);
};

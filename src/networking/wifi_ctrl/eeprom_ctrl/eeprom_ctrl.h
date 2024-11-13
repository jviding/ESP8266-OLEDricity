#pragma once

#include <Arduino.h>
#include <EEPROM.h>

#define EEPROM_SIZE 512

// First byte to indicate if SSID and PWD exist
#define INIT_ADDR 0x00
#define INIT_VAL  0x3A

// Second byte to start SSID and PWD Strings
// Format:
// - First byte for String length
// - Followed by String itself
// - No EOF char '\0'
#define CREDENTIALS_START_ADDR 1


class Eeprom_ctrl {
public:
  // Functions
  static void init();
  static bool clear_SSID_and_password();
  static bool read_SSID_and_password(char** ssid, char** password);
  static bool write_SSID_and_password(char* ssid, char* password);

private:
  // Functions
  static bool has_SSID_and_password();
  static int read_string_from_eeprom(char** str, int addr);
  static int get_string_length(char* str);
  static int write_string_to_eeprom(char* str, int addr);
};

#include "eeprom_ctrl.h"


void Eeprom_ctrl::init() {
  EEPROM.begin(EEPROM_SIZE);
  Serial.println("EEPROM: Initialized.");
};

bool Eeprom_ctrl::clear_SSID_and_password() {
  Serial.println("EEPROM: Clearing SSID and Password.");
  EEPROM.write(INIT_ADDR, 0x00);
  if (EEPROM.commit()) return true;
  Serial.println("EEPROM: Failed committing changes.");
  return false;
};

bool Eeprom_ctrl::has_SSID_and_password() {
  if (EEPROM.read(INIT_ADDR) == INIT_VAL) return true;
  Serial.println("EEPROM: SSID and Password not set.");
  return false;
};

// Returns length of the read String
int Eeprom_ctrl::read_string_from_eeprom(char** str, int addr) {
  // First byte is length
  int len = EEPROM.read(addr);
  if (addr + 1 + len > EEPROM_SIZE) {
    Serial.println("EEPROM: Read error, index out of bounds.");
    return -1;
  }
  // Allocate String
  (*str) = new char[len + 1];
  (*str)[len] = '\0';
  // Read String
  for (int i = 0; i < len; i++) {
    (*str)[i] = EEPROM.read(addr + 1 + i);
  }
  return len;
};

bool Eeprom_ctrl::read_SSID_and_password(char** ssid, char** password) {
  Serial.println("EEPROM: Reading WiFi credentials...");
  if (!has_SSID_and_password()) return false;
  // Read SSID
  int addr = CREDENTIALS_START_ADDR;
  int len = read_string_from_eeprom(ssid, addr);
  if (len == -1) return false;
  Serial.println("EEPROM: SSID ok.");
  // Read PWD
  addr += len + 2;
  len = read_string_from_eeprom(password, addr);
  if (len == -1) {
    delete[] *ssid;
    *ssid = nullptr;
    return false;
  }
  Serial.println("EEPROM: Password ok.");
  return true;
};

int Eeprom_ctrl::get_string_length(char* str) {
  int len = 0;
  while (str[len] != '\0') len++;
  return len;
};

// Returns length of written String
int Eeprom_ctrl::write_string_to_eeprom(char* str, int addr) {
  int len = get_string_length(str);
  // Notice +1 byte for Length
  if (addr + len > EEPROM_SIZE) {
    Serial.println("EEPROM: Write error, index out of bounds.");
    return -1;
  }
  // First byte is length
  EEPROM.write(addr, len);
  // Write String
  for (int i = 0; i < len; i++) {
    EEPROM.write(addr + 1 + i, str[i]);
  }
  return len;
};

bool Eeprom_ctrl::write_SSID_and_password(char* ssid, char* password) {
  Serial.println("EEPROM: Writing WiFi credentials...");
  // Write SSID
  int addr = CREDENTIALS_START_ADDR;
  int len = write_string_to_eeprom(ssid, addr);
  if (len == -1) return false;
  Serial.println("EEPROM: SSID ok.");
  // Write Password
  addr += len + 2;
  len = write_string_to_eeprom(password, addr);
  if (len == -1) return false;
  Serial.println("EEPROM: Password ok.");
  // Write OK
  EEPROM.write(INIT_ADDR, INIT_VAL);
  // Commit changes
  if (!EEPROM.commit()) {
    Serial.println("EEPROM: Failed committing changes.");
    return false;
  }
  return true;
};

#include "wifi_ctrl.h"

char* WiFi_ctrl::SSID = nullptr;
char* WiFi_ctrl::PWD = nullptr;


bool WiFi_ctrl::init() {
  Serial.println("WiFi: Initializing...");
  Eeprom_ctrl::init();
  Server_ctrl::init();
  if (!Eeprom_ctrl::read_SSID_and_password(&SSID, &PWD)) {
    Serial.println("WiFi: Logon credentials missing.");
    return false;
  }
  return true;
};

bool WiFi_ctrl::is_connected() {
  return WiFi.status() == WL_CONNECTED;
};

bool WiFi_ctrl::is_connecting() {
  switch(WiFi.status()) {
    case WL_NO_SSID_AVAIL:
      Serial.println("SSID not available, incorrect?");
      return false;
    case WL_CONNECT_FAILED:
      Serial.println("Failed, incorrect password?");
      return false;
    case WL_IDLE_STATUS:
      Serial.println("Module is idle.");
      return false;
    default:
      return true;
  }
};

bool WiFi_ctrl::try_connect() {
  int time = 0;
  if (!WiFi.mode(WIFI_STA)) {
    Serial.println("WiFi: Something went wrong while trying to connect.");
    return false;
  }
  Serial.print("WiFi: Connecting..");  
  WiFi.begin(SSID, PWD);
  while (!is_connected() && is_connecting() && time < 15) {
    Serial.print(".");
    delay(1000);
    time++;
  }
  if (!is_connected()) return false;
  Serial.println("Ok.");
  return true;
};

bool WiFi_ctrl::connect() {
  if (is_connected()) {
    Serial.println("WiFi: Already connected.");
  } else if (!try_connect()) {
    Serial.println("WiFi: Failed.");
    return false;  
  }
  Serial.print("WiFi: IP address is "); Serial.println(WiFi.localIP());
  return true;
};

bool WiFi_ctrl::disconnect() {
  if (!is_connected()) {
    Serial.println("WiFi: Already disconnected.");
    return true;
  } else if (WiFi.disconnect()) {
    Serial.println("WiFi: Disconnected.");
    return true;
  } else {
    Serial.println("WiFi: Failed disconnecting.");
    return false;
  }
};

void WiFi_ctrl::generate_random_8_digit_password(char** password) {
  *password = new char[9];
  (*password)[8] = '\0';
  for (int i = 0; i < 8; i++) {
    (*password)[i] = '0' + random(10); // ASCII conversion
  }
};

void WiFi_ctrl::ip_address_to_str(IPAddress IP, char** ip_address) {
  int len = IP.toString().length();
  *ip_address = new char[len + 1]; // +1 for '\0'
  (*ip_address)[len] = '\0';
  strcpy(*ip_address, IP.toString().c_str());
};

bool WiFi_ctrl::hotspot_enable(char* name, char** password, char** ip_address) {
  Serial.print("WiFi: HotSpot starting...");
  // Create password  
  if (*password == nullptr) generate_random_8_digit_password(password);
  // Try open HotSpot
  WiFi.mode(WIFI_AP);
  if (!WiFi.softAP(name, *password)) {
    Serial.println("Failed.");
    return false;
  }
  Serial.println("Ok.");
  // Get IP address
  if (*ip_address == nullptr) {
    IPAddress IP = WiFi.softAPIP();
    ip_address_to_str(IP, ip_address);
  }
  // Log WiFi details
  Serial.println(" - SSID: Electricube");
  Serial.print(" - Password: "); Serial.println(*password);
  Serial.print(" - IP address: "); Serial.println(*ip_address);
  return true;
};

bool WiFi_ctrl::hotspot_disable() {
  if (WiFi.softAPdisconnect()) {
    Serial.println("WiFi: HotSpot disabled.");
    return true;
  } else {
    Serial.println("WiFi: Failed disabling HotSpot.");
    return false;
  }
};

bool WiFi_ctrl::set_WiFi_SSID_and_password() {
  Serial.println("WiFi: Started setting new WiFi credentials.");
  if (SSID != nullptr) delete[] SSID;
  if (PWD != nullptr) delete[] PWD;
  bool res_ok = true;
  // Get new
  Server_ctrl::run(&SSID, &PWD);
  // Clear old
  res_ok = res_ok && Eeprom_ctrl::clear_SSID_and_password();
  // Write to memory
  res_ok = res_ok && Eeprom_ctrl::write_SSID_and_password(SSID, PWD);
  delay(1000);
  // Done
  if (!res_ok) {
    Serial.println("WiFi: Failed.");
  }
  return res_ok;
};

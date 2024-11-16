#include "wifi_ctrl.h"

char* WiFi_ctrl::SSID = nullptr;
char* WiFi_ctrl::PWD = nullptr;


bool WiFi_ctrl::init() {
  Serial.println("WiFi: Initializing...");
  Eeprom_ctrl::init();
  Server_ctrl::init();
  if (Eeprom_ctrl::read_SSID_and_password(&SSID, &PWD)) {
    return true;
  }
  Serial.println("WiFi: Failed.");
  return false;
};

bool WiFi_ctrl::is_connected() {
  return WiFi.status() == WL_CONNECTED;
};

void WiFi_ctrl::connect() {
  if (is_connected()) {
    Serial.println("WiFi: Already connected.");
  } else {
    Serial.print("WiFi: Connecting..");
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PWD);
    while (is_connected() == false) {
      Serial.print(".");
      delay(1000);
    }
    Serial.println("Ok.");
  }
  Serial.print("WiFi: IP address is "); Serial.println(WiFi.localIP());
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

bool WiFi_ctrl::hotspot_enable(char** ip_address, char** password) {
  Serial.println("WiFi: HotSpot starting...");
  Serial.println(" - Name: Electricube");
  // Create password  
  generate_random_8_digit_password(password);
  Serial.print(" - Password: "); Serial.println(*password);
  // Open HotSpot
  WiFi.mode(WIFI_AP);
  if (WiFi.softAP("Electricube", *password)) {
    IPAddress IP = WiFi.softAPIP();
    ip_address_to_str(IP, ip_address);
    Serial.print(" - IP address:"); Serial.println(*ip_address);
    Serial.println("WiFi: HotSpot started.");
    return true;
  } else {
    Serial.println("WiFi: Failed.");
    return false;
  }
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
  // Clear old
  res_ok = res_ok && Eeprom_ctrl::clear_SSID_and_password();
  // Get new
  Server_ctrl::run(&SSID, &PWD);
  // Write to memory
  res_ok = res_ok && Eeprom_ctrl::write_SSID_and_password(SSID, PWD);
  // Done
  if (!res_ok) {
    Serial.println("WiFi: Failed.");
  }
  return res_ok;
};

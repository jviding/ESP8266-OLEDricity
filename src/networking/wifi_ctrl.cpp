#include "networking.h"


bool Networking::wifi_is_connected() {
  return WiFi.status() == WL_CONNECTED;
};

void Networking::wifi_connect() {
  Serial.print("WiFi: Starting..");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PWD);
  while (wifi_is_connected() == false) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("OK.");
};

void Networking::wifi_disconnect() {
  WiFi.disconnect();
  Serial.println("WiFi: Disconnected.");
};

void Networking::wifi_ensure_is_connected() {
  if (wifi_is_connected() == false) {
    wifi_connect();
  } else {
    Serial.println("WiFi: Already connected.");
  }
};

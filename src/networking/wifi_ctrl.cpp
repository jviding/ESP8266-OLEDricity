#include "networking.h"


bool Networking::wifi_is_connected() {
  return WiFi.status() == WL_CONNECTED;
};

void Networking::wifi_enable() {
  Serial.print("WiFi starting..");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PWD);
  while (wifi_is_connected() == false) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Started.");
};

void Networking::wifi_reconnect() {
  WiFi.reconnect();
  Serial.print("WiFi reconnecting..");
  while (wifi_is_connected() == false) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Reconnected.");
};

void Networking::wifi_disconnect() {
  WiFi.disconnect();
  Serial.println("WiFi disconnected.");
};

void Networking::wifi_ensure_is_connected() {
  if (wifi_is_connected() == false) {
    wifi_reconnect();
  } else {
    Serial.println("WiFi was already connected.");
  }
};

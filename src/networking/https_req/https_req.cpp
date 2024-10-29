#include "https_req.h"

HTTPClient HTTPS_req::https;
BearSSL::WiFiClientSecure HTTPS_req::client;


void HTTPS_req::enable() {
  client.setInsecure();
  Serial.println("HTTPS: Enabled.");
  Serial.println("HTTPS: Disabled certificate validation.");
};

int HTTPS_req::get_data(https_t** raw_data) {
  // Initialize client
  if (!https.begin(client, API_URL)) {
    Serial.println("HTTPS: Failed initializing client.");
    return -1;
  }
  // Allocate memory
  char** buffs = nullptr;
  int buffs_num;
  // Send request
  Serial.print("HTTPS: Connecting...");
  int httpCode = https.GET();
  // Read response
  if (httpCode == HTTP_CODE_OK) {
    Serial.println("OK.");
    buffs = new char*[BUFFERS_MAX_NUM];
    buffs_num = read_to_buffers(https.getStreamPtr(), buffs, BUFFERS_MAX_NUM, BUFFER_SIZE);
  } else {
    Serial.print(httpCode > 0 ? "\nHTTPS: Unexpected response code: " : "\nHTTPS: Network error: "); Serial.println(httpCode);
    buffs_num = -1;
  }
  // Close
  https.end();
  *raw_data = new https_t{buffs_num, BUFFER_SIZE, buffs};
  return buffs_num;
};

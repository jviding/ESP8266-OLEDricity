#include "networking.h"

HTTPClient Networking::https;
BearSSL::WiFiClientSecure Networking::client;


void Networking::https_enable() {
  client.setInsecure();
  Serial.println("Disabled certificate validation.");
};

// Returns the number of bytes read to buffer
int Networking::https_read_to_buffer(Stream* response, char* buff, size_t buff_size) {
  /*
  * Data is read in as chunks, where chunk size is 1/2 of buffer size.
  * If the buffer size is changed, this code might need to be changed.
  * Otherwise, the ESP8266 may have issues with performance and memory.
  */
  // Read in 2x chunks, where chunk is 1/2 of buffer size
  size_t half_1 = response->readBytes(&buff[0], buff_size/2);
  size_t half_2 = response->readBytes(&buff[buff_size/2], buff_size/2);
  // Return total bytes received
  return half_1 + half_2;
};

// Success: Returns the number of allocated buffers
// Failure: Allocated buffers are freed, and returns -1
int Networking::https_read_response(Stream* response, char** buffs, size_t buffs_num, size_t buff_size) {
  Serial.print("Reading response...");
  for (size_t i = 0; i < buffs_num; i++) {
    // Allocate new buffer
    buffs[i] = new char[buff_size];
    // Receive streamed response to buffer
    int bytes_read = https_read_to_buffer(response, buffs[i], buff_size);
    // If buffer is not full, it means end of response
    if (bytes_read < (int)buff_size) {
      buffs[i][bytes_read] = '\0';  // Add termination char to mark end of buffered stream
      Serial.print("Allocated ");
      Serial.print(i + 1);
      Serial.println(" buffers.");
      return i + 1;                 // Notice i is index, where +1 for number of buffers
    }
  }
  // Overflow, free all memory and return -1 to signal error
  Serial.println("\nBuffer overflow, API response was too large.");
  for (int i = 0; i < (int)buffs_num; i++) {
    delete[] buffs[i];
  }
  return -1;
};

// Success: Returns number of allocated buffers
// Failure: Returns -1
int Networking::https_call_API(char** buffs, size_t buffs_num, size_t buff_size) {
  // Response
  int alloc_num = 0;
  // Initialize the HTTP client
  if (!https.begin(client, API_URL)) {
    Serial.println("Failed initializing HTTP client.");
    return -1;
  }
  Serial.print("Sending HTTPS GET...");
  // GET request to API
  int httpCode = https.GET();
  // Handle response
  if (httpCode == HTTP_CODE_OK) {
    Serial.println("Sent.");    
    alloc_num = https_read_response(https.getStreamPtr(), buffs, buffs_num, buff_size);
  } else {
    Serial.println("Failed.");
    Serial.print(httpCode > 0 ? "Unexpected response code: " : "Network error: ");
    Serial.println(httpCode);
    alloc_num = -1;
  }
  https.end();
  return alloc_num;
};

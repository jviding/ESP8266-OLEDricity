#include "https_req.h"

HTTPClient HTTPS_req::https;
BearSSL::WiFiClientSecure HTTPS_req::client;


void HTTPS_req::init() {
  client.setInsecure();
  Serial.println("HTTPS: Initialized.");
  Serial.println("HTTPS: Disabled certificate validation.");
};

// Return number of bytes read to buffer
int HTTPS_req::read_to_buffer(Stream* response, char* buff, size_t buff_size) {
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

// Return number of allocated buffers, or -1 if failed
int HTTPS_req::read_to_buffers(Stream* response, char*** buffs, size_t buffs_max_num, size_t buff_size) {
  *buffs = new char*[buffs_max_num];
  for (size_t i = 0; i < buffs_max_num; i++) {
    // Allocate new buffer and read from streamed response
    (*buffs)[i] = new char[buff_size];
    int bytes_read = read_to_buffer(response, (*buffs)[i], buff_size);
    // If buffer is not full, reached end of streamed response
    if (bytes_read < (int)buff_size) {
      (*buffs)[i][bytes_read] = '\0';  // Add termination char to mark end of buffered stream
      //Serial.print("HTTPS: Allocated "); Serial.print(i + 1); Serial.println(" buffers for raw data.");
      return i + 1;                 // Notice i is index, where +1 for number of buffers
    }
  }
  Serial.println("HTTPS: Buffer overflow while reading response.");
  Serial.println("HTTPS: Freeing allocated buffers.");
  for (size_t i = 0; i < buffs_max_num; i++) {
    delete[] (*buffs)[i];
  }
  delete[] *buffs;
  return -1;
};

int HTTPS_req::get_raw_data(char*** buffs, size_t buffs_max_num, size_t buff_size) {
  int buffs_num = -1;
  // Initialize client
  if (!https.begin(client, API_URL)) {
    Serial.println("HTTPS: Failed initializing client.");
    return -1;
  }
  // Send request
  int httpCode = https.GET();
  if (httpCode == HTTP_CODE_OK) {
    Serial.println("HTTPS: Reading raw response...");
    buffs_num = read_to_buffers(https.getStreamPtr(), buffs, buffs_max_num, buff_size);
  } else if (httpCode > 0) {
    Serial.print("HTTPS: Unexpected response code: "); Serial.println(httpCode);
  } else {
    Serial.print("HTTPS: Network error: "); Serial.println(httpCode);
  }
  // Close
  https.end();
  return buffs_num;
};

bool HTTPS_req::get_price_data(price_data_t** data) {
  Serial.println("HTTPS: Sending request...");
  // Send request and read raw response
  char** buffs = nullptr;
  int buffs_num = get_raw_data(&buffs, BUFFERS_MAX_NUM, BUFFER_SIZE);
  if (buffs_num == -1) return false;
  // Parse raw response to data
  https_t* raw_data = new https_t{buffs_num, BUFFER_SIZE, buffs};
  return Parser::get_price_data(raw_data, data);
};

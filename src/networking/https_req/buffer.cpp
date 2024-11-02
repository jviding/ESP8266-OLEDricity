#include "https_req.h"


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
int HTTPS_req::read_to_buffers(Stream* response, char** buffs, size_t buffs_max_num, size_t buff_size) {
  Serial.println("HTTPS: Reading response.");
  for (size_t i = 0; i < buffs_max_num; i++) {
    // Allocate new buffer and read from streamed response
    buffs[i] = new char[buff_size];
    int bytes_read = read_to_buffer(response, buffs[i], buff_size);
    // If buffer is not full, reached end of streamed response
    if (bytes_read < (int)buff_size) {
      buffs[i][bytes_read] = '\0';  // Add termination char to mark end of buffered stream
      Serial.print("HTTPS: Allocated "); Serial.print(i + 1); Serial.println(" buffers for raw data.");
      return i + 1;                 // Notice i is index, where +1 for number of buffers
    }
  }
  // Overflow, release memory
  Serial.println("HTTPS: Buffer overflow, releasing allocated memory.");
  for (int i = 0; i < (int)buffs_max_num; i++) {
    delete[] buffs[i];
  }
  delete[] buffs;
  return -1;
};
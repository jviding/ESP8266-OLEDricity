#include "server_ctrl.h"

ESP8266WebServer Server_ctrl::server(80);

char* Server_ctrl::i_ssid = nullptr;
char* Server_ctrl::i_pwd = nullptr;


void Server_ctrl::init() {
  server.on("/", HTTP_GET, get);
  server.on("/", HTTP_POST, post);
  Serial.println("Server: Initialized.");
};

void Server_ctrl::get() {
  Serial.println("Server: Received GET.");
  server.send(200, "text/html", HTML_FORM);
};

void Server_ctrl::post() {
  Serial.println("Server: Received POST.");
  if (server.hasArg("ssid") && server.hasArg("pwd")) {
    // Free if allocated
    if (i_ssid != nullptr) delete[] i_ssid;
    if (i_pwd != nullptr) delete[] i_pwd;
    // Allocate memory for new values
    i_ssid = new char[server.arg("ssid").length() + 1]; // +1 for '\0'
    i_pwd = new char[server.arg("pwd").length() + 1];
    // Copy
    strcpy(i_ssid, server.arg("ssid").c_str());
    strcpy(i_pwd, server.arg("pwd").c_str());
    server.send(200, "text/plain", "Thank you.");
  } else {
    server.send(400, "text/plain", "Something went wrong.");
  }
};

void Server_ctrl::run(char** ssid, char** password) {
   // Start server
  server.begin();
  Serial.println("Server: Started, listening for connections...");
  // Handle requests
  while (i_ssid == nullptr && i_pwd == nullptr) {
    server.handleClient();
  }
  // Set WiFi credentials
  Serial.println("Server: WiFi Logon credentials received.");
  *ssid = i_ssid;
  *password = i_pwd;
  i_ssid = nullptr;
  i_pwd = nullptr;
  Serial.print(" - SSID: "); Serial.println(*ssid);
  Serial.print(" - Password: "); Serial.println(*password);
  // Stop
  server.stop();
  Serial.println("Server: Stopped.");
};

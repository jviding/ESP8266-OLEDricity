#pragma once

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "html_form.h"

#define HTTP_PORT 80


class Server_ctrl {
public:
  // Functions
  static void init();
  static void run(char** ssid, char** password);

private:
  // Variables
  static ESP8266WebServer server;
  static char* i_ssid;
  static char* i_pwd;

  // Functions
  static void get();
  static void post();
};

#ifndef WIFI_CONFIG_H
#define WIFI_CONFIG_H

#include <ESP8266httpUpdate.h>

extern const char* ssid;
extern const char* password;
String getMacAddress();
#endif

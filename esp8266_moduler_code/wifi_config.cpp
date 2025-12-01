#include "wifi_config.h"

const char* ssid = "Jio_Respirer";
const char* password = "Respirer@789!";

String getMacAddress() {
  String imei = WiFi.macAddress();
  imei.replace(":", "");  // REMOVE ALL COLONS
  return imei;

}

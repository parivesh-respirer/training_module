#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <PCA9554.h>  // Load the PCA9554 Library
#include "pca.h"
#include "pms.h"
#include "ec200.h"
#include "timer.h"
#include "function.h"
#include "wifi_config.h"

int value1 = 33, value2 = 44;
char saveBuf[200];
char imeiStr[15];
uint32_t startt = 0;

int atcount = 0;

// String getMacAddress() {
//   String imei = WiFi.macAddress();
//   imei.replace(":", "");  // REMOVE ALL COLONS
//   return imei;
//   // Serial.println(WiFi.macAddress());
//   // return WiFi.macAddress();
// }

void setup() {

  pmsSerial.begin(9600);
  Serial.begin(115200);
  Wire.begin();
  initPMS();
  init_pca_on_board_gpio();
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
    Serial.println("\nWiFi connected!");
  Serial.println(WiFi.macAddress());

  init_ec();  // it is not necessary
  delay(100);
  setup_ec();
  Serial.println("PMS started...");
  Serial.println("Begin...");
  strcpy(imeiStr, "C8C9A3929102");
  init_tasks();
  Register_task(send_data_to_server, 10000);
  Register_task(readPMS,100);
}


void loop() {

  //   atcount++;
  // Serial.print("attempt number: ");
  // Serial.println(atcount);
  read_io();
  Run_tasks();
// if (WiFi.status() == WL_CONNECTED) {
//       HTTPClient http;
//       http.begin("http://api.urbansciences.in:80/quartz/bulk_rawdata");
//       http.addHeader("Content-Type", "application/json");
//       http.setTimeout(5000);
// String payload =  String("[{\"imei\":\"") + getMacAddress()
//                   //  + "\",\"timestr2\":\"" + getFormattedTime1()
//                    + "\",\"pm10cnc\":\"" + String(23)
//                                       + "\"}]";
//   Serial.print("Payload: ");
//   Serial.println(payload);

//       int code = http.POST(payload);
//       Serial.print("HTTP Response Code: ");
//       Serial.println(code);

//       http.end();

// }

}

#include <Arduino.h>
// #include <Wire.h>
#include <SoftwareSerial.h>
#include <PCA9554.h>  // Load the PCA9554 Library
#include "pca.h"
#include "pms.h"
#include "ec200.h"

int atcount = 0;

void setup() {

  // pmsSerial.begin(9600);
  Serial.begin(115200);
  initPMS();
  Serial.println("PMS started...");


  Serial.println("Begin...");
  Wire.begin();
  init_pca_on_board_gpio();
  read_io();
  // set_io();
  delay(100);
  setup_ec();
}

void loop() {

  readPMS();
  Serial.println();

  atcount++;
  Serial.print("attempt number: ");
  Serial.println(atcount);
  read_io();

  while (Serial.available()) Serial.read();
  Serial.print("ATI\r\n");
  delay(100);
  wait_for_at_response();
  delay(1000);

  // Serial.print("AT+QHTTPCFG=\"contextid\",1\r\n");
  while (Serial.available()) Serial.read();
  Serial.print("ATE0\r\n");
  wait_for_at_response();
  delay(1000);
}

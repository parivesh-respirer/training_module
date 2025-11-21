#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <PCA9554.h>  // Load the PCA9554 Library
#include "pca.h"
#include "pms.h"
#include "ec200.h"
#include "timer.h"

int value1 = 33, value2 = 44;
char saveBuf[200];
char imeiStr[15];
uint32_t startt = 0;
Cleaner Sweeper;
int atcount = 0;


void demo_timer(void){
      Sweeper.clear_stream_buff();
    sendDataToServer();
    Sweeper.clear_stream_buff();
}


void setup() {

  pmsSerial.begin(9600);
  Serial.begin(115200);
  Wire.begin();
  initPMS();
  Serial.println("PMS started...");
  Serial.println("Begin...");
  init_pca_on_board_gpio();
  init_ec();  // it is not necessary
  delay(100);
  setup_ec();
  strcpy(imeiStr, "C8C9A3929102");
  init_tasks();
  Register_task(demo_timer,20000);
}


void loop() {

  //   atcount++;
  // Serial.print("attempt number: ");
  // Serial.println(atcount);

  read_io();
  Run_tasks();
  // while (millis() - startt > 20000) {
  //   startt = millis();
  //   Sweeper.clear_stream_buff();
  //   sendDataToServer();
  //   Sweeper.clear_stream_buff();
  // }
}

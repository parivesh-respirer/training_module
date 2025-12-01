#include "ec200.h"
#include <Arduino.h>
#include "pca.h"
#include <string.h>
#include "sensor.h"
#include <stdio.h>
#include "wifi_config.h"

char stream_buffer_arr[650];
unsigned long start = millis();
uint32_t time_out_cnt;
char at_buffer[200];
void Cleaner::clear_stream_buff() {
  int buffer_size = strlen(stream_buffer_arr);

  for (int i = 0; i < buffer_size; i++) {
    stream_buffer_arr[i] = '\0';
  }
}

void wait_for_at_response(void) 

{
    uint32_t timeout = time_out_cnt;
    uint32_t start = millis();

    int index = 0;

    // wait until first byte arrives OR timeout
    while (!Serial.available() && (millis() - start < timeout)) {
        read_io();
    }

    start = millis();
    
    while (Serial.available() && (millis() - start < timeout)) {

        char c = Serial.read();

        // store safely in buffer (minus 1 for null terminator)
        if (index < sizeof(at_buffer) - 1) {
            at_buffer[index++] = c;
        }

        read_io();
        delay(1);   // small delay just like your first code
    }
}


void setup_ec(void) {
  enable4GSerial();
  // writeRegister(REG_CONFIG, 0x07);


  delay(200);
  writeRegister_ec(REG_CONFIG, 0x00);

  writeRegister_ec(REG_OUTPUT, 0x00);
  for (int i = 0; i < 15; i++) {
    delay(100);
    //     readFG();
    read_io();
  }
  while (Serial.available()) Serial.read();

  writeRegister_ec(REG_OUTPUT, 0x04);
  for (int i = 0; i < 22; i++) {
    delay(100);
    //     readFG();
    read_io();
  }
  while (Serial.available()) Serial.read();


  writeRegister_ec(REG_OUTPUT, 0x00);
  for (int i = 0; i < 10; i++) {
    delay(100);
    //     readFG();
    read_io();
  }
  while (Serial.available()) Serial.read();


  Serial.flush();
  while (Serial.available()) Serial.read();  // clear previous noise
  Serial.print("AT\r\n");
  delay(100);
  wait_for_at_response();
  delay(1000);

  Serial.print("ATE0\r\n");
  delay(100);
  wait_for_at_response();
  delay(1000);

  Serial.print("AT+QICSGP=2,1,\"airtelgprs.com\",\"\",\"\",1\r\n");
  delay(100);
  wait_for_at_response();
  delay(1000);

  Serial.print("AT+QICSGP=2,1,\"\",\"\",\"\",1\r\n");
  delay(100);
  wait_for_at_response();
  delay(1000);

  Serial.print("AT+QHTTPCFG=\"contextid\",1\r\n");
  delay(100);
  wait_for_at_response();
  delay(1000);


  Serial.print("AT+QHTTPCFG=\"responseheader\",1\r\n");
  delay(100);
  wait_for_at_response();
  delay(1000);

  Serial.flush();
}


void init_ec(void) {
  writeRegister_ec(REG_CONFIG, 0x00);
  delay(100);
  writeRegister_ec(REG_OUTPUT, 0x00);
  for (int i = 0; i < 10; i++) {
    delay(100);
    //      readFG();
    read_io();
  }

  writeRegister_ec(REG_OUTPUT, 0x08);
  for (int i = 0; i < 10; i++) {
    delay(100);
    //        readFG();
    read_io();
  }
  writeRegister_ec(REG_OUTPUT, 0x00);
  for (int i = 0; i < 50; i++) {
    delay(100);
    //        readFG();
    read_io();
  }
  writeRegister_ec(REG_OUTPUT, 0x04);
  for (int i = 0; i < 22; i++) {
    delay(100);
    //     readFG();
    read_io();
  }
  writeRegister_ec(REG_OUTPUT, 0x00);
  for (int i = 0; i < 50; i++) {
    delay(100);
    //     readFG();
    read_io();
  }
}



void sendDataEC200() {
  enable4GSerial();
  delay(100);
  Serial.flush();
  Serial.print("AT+CSQ\r\n");
  time_out_cnt = 300;
  // waitForResponse();
  wait_for_at_response();
  //  Serial.println(test);
  delay(100);
  Serial.flush();

#ifdef sDebug
  //Serial.flush();
#endif

  Serial.print("AT+CREG?\r\n");
  //  sprintf(saveBuf + strlen(saveBuf), "%s,", "CREG");
  wait_for_at_response();
  time_out_cnt = 300;
  // waitForResponse();
  delay(100);
#ifdef sDebug
  //Serial.flush();
#endif

  Serial.print("AT+CGATT?\r\n");
  sprintf(saveBuf + strlen(saveBuf), "%s,", "CGATT");
  wait_for_at_response();
  time_out_cnt = 30000;
  // waitForResponse();
  delay(100);
  // #ifdef sDebug
  //   //Serial.flush();
  // #endif

  // if(timeout_flg==0)
  // {


  Serial.print("AT+QIACT=1\r\n");
  sprintf(saveBuf + strlen(saveBuf), "%s,", "QIACT");
  wait_for_at_response();
  time_out_cnt = 30000;
  // waitForResponse();
  delay(100);
#ifdef sDebug
  //Serial.flush();
#endif




  sprintf(stream_buffer_arr + strlen(stream_buffer_arr), "&lat=%s&lon=%s", "12.971600", "77.594600");



  //  sprintf(stream_buffer_arr + strlen(stream_buffer_arr), "\r\n");
  //-------------------------------- Kirti commented this to send real time data ------------------------------------------------------//

  char len[4];
  sprintf(len, "%d", strlen(stream_buffer_arr));

  char temp[25];
  for (int i = 0; i < 24; i++) {
    temp[i] = '\0';
  }

  sprintf(temp + strlen(temp), "AT+QHTTPURL=");
  sprintf(temp + strlen(temp), "%s", len);
  sprintf(temp + strlen(temp), ",30\r\n");
  Serial.flush();
  Serial.print(temp);
  //  sprintf(saveBuf + strlen(saveBuf), "%s,", "QHTTPURL");
  time_out_cnt = 30000;
  // waitForResponse();
  wait_for_at_response();
  delay(100);
#ifdef sDebug
  //Serial.flush();
#endif

  Serial.print(stream_buffer_arr);
  Serial.print("\r\n");
  // sprintf(saveBuf + strlen(saveBuf), "%s,", "buffer");
  wait_for_at_response();
  time_out_cnt = 30000;
  // waitForResponse();
  delay(100);
#ifdef sDebug
  //Serial.flush();
#endif

  //  Serial.begin(115200);
  Serial.flush();
  Serial.print("AT+QHTTPGET=30\r\n");
  sprintf(saveBuf + strlen(saveBuf), "%s,", "QHTTPGET");
  time_out_cnt = 12000;
  // waitForResponse();
  wait_for_at_response();
  delay(100);

  //  Serial.flush();
}
void sendDataToServer() {

  enable4GSerial();
  delay(40);

  Serial.flush();

  sprintf(stream_buffer_arr + strlen(stream_buffer_arr), "http://api.urbansciences.in:80/quartz/rawdata?");
  strcat(stream_buffer_arr, "&imei=");
  strcat(stream_buffer_arr,getMacAddress().c_str());

  formSensorData();
   if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin("http://api.urbansciences.in:80/quartz/bulk_rawdata");
      http.addHeader("Content-Type", "application/json");
      http.setTimeout(5000);
  Serial.print("Payload: ");
  Serial.println(payload);

      int code = http.POST(payload);
      Serial.print("HTTP Response Code: ");
      Serial.println(code);

      http.end();
      Serial.println("sent through wifi....");
   }else{
sendDataEC200();
   }
  
}

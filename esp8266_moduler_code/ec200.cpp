#include "ec200.h"
#include <Arduino.h>
#include "pca.h"
#include <string.h>
#include "sensor.h"
#include <stdio.h> 

char stream_buffer_arr[650];


// Cleaner Sweeper;
uint32_t time_out_cnt;

void Cleaner::clear_stream_buff() {
  int buffer_size = strlen(stream_buffer_arr);

  for (int i = 0; i < buffer_size; i++) {
    stream_buffer_arr[i] = '\0';
  }
}


void waitForResponse()
{ 
  char Response[100];
  char c;
  int i;
  uint32_t timeOut = 10000, timer = millis();
  static uint8_t readyCheck = 0;
  static uint8_t timeoutCount = 0;


timeOut = time_out_cnt;
  while ((!Serial.available()) && (millis() - timer < timeOut))
  {
    // yield();
//    if (readyCheck == 0)
//    {
//      timeOut = 120000;
//      readyCheck = 1;
//    }
   read_io();
   //  readFG();
 
  }


  timer = millis();

  while ((Serial.available()) && (millis() - timer < timeOut))
  {
    //    c = Serial.read();
    Response[i] = Serial.read();;
    i++;

    delay(2);
    read_io();
  
  }

}

void wait_for_at_response(void) {
//   uint32_t timeOut = 3000, timer = millis();  // increased timeout for slow responses
//   char temp[200];
//   int i = 0;
// for (int j= 0; j < 200; j++)
//     saveBuf[j] = '\0';

//   // Wait for response or timeout
//   while ((millis() - timer < timeOut)) {
    
//     if (Serial.available()) {
//       char c = Serial.read();
//       if (i < sizeof(temp) - 1) {
//         temp[i++] = c;
//       }
//       delay(1);
//     }
//   }

//   // Terminate string to prevent garbage print
//   temp[i] = '\0';

//   // Filter out unreadable characters
//   Serial.print("data is: ");
//   for (int j = 0; j < i; j++) {
//     if (isPrintable(temp[j]) || temp[j] == '\r' || temp[j] == '\n') {
//       Serial.print(temp[j]);
//     }
//   }

//   Serial.println();
// void wait_for_at_response() {
  unsigned long start = millis();
  unsigned long timeout = 5000;

  // clear buffer
  int idx = 0;
  memset(saveBuf, 0, sizeof(saveBuf));

  while (millis() - start < timeout) {

    while (Serial.available()) {
      char c = Serial.read();
      if (idx < sizeof(saveBuf) - 1) {
        saveBuf[idx++] = c;
      }

      // If modem ends the reply → STOP
      if (strstr(saveBuf, "\r\nOK\r\n") != NULL ||
          strstr(saveBuf, "\r\nERROR\r\n") != NULL) 
      {
        goto PRINT_DATA;
      }
    }
  }

PRINT_DATA:
  Serial.print("data is: ");
  for (int i = 0; i < idx; i++) {
    if (isPrintable(saveBuf[i]) || saveBuf[i] == '\r' || saveBuf[i] == '\n')
      Serial.print(saveBuf[i]);
  }
  Serial.println();
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
  for (int i = 0; i < 10; i++)
  {
      delay(100);
//      readFG();
        read_io();
  }

  writeRegister_ec(REG_OUTPUT, 0x08);
   for (int i = 0; i < 10; i++)
      {
        delay(100);
//        readFG();
        read_io();
      }
        writeRegister_ec(REG_OUTPUT, 0x00);
        for (int i = 0; i < 50; i++)
      {
        delay(100);
//        readFG();
        read_io();
      }
      writeRegister_ec(REG_OUTPUT, 0x04);
         for (int i = 0; i < 22; i++)
  {
    delay(100);
//     readFG();
     read_io();
  }
          writeRegister_ec(REG_OUTPUT, 0x00);
   for (int i = 0; i < 50; i++)
  {
    delay(100);
//     readFG();
     read_io();
  }
}



void sendDataEC200()
{
  enable4GSerial();
    delay(100);

//  ioCon2.digitalWrite(6, HIGH); //SetupEC200
//  ioCon2.digitalWrite(7, HIGH);
  Serial.flush();

  Serial.print("AT+CSQ\r\n");
 // sprintf(saveBuf + strlen(saveBuf), "%s,", "CSQ");
 time_out_cnt = 300;
  waitForResponse();
          // wait_for_at_response();
//  Serial.println(test);
  delay(100);
  Serial.flush();
   
#ifdef sDebug
  //Serial.flush();
#endif

  Serial.print("AT+CREG?\r\n");
//  sprintf(saveBuf + strlen(saveBuf), "%s,", "CREG");
          // wait_for_at_response();
          time_out_cnt = 300;
  waitForResponse();
  delay(100);
#ifdef sDebug
  //Serial.flush();
#endif

  Serial.print("AT+CGATT?\r\n");
  sprintf(saveBuf + strlen(saveBuf), "%s,", "CGATT");
          // wait_for_at_response();
          time_out_cnt = 30000;
  waitForResponse();
  delay(100);
// #ifdef sDebug
//   //Serial.flush();
// #endif

// if(timeout_flg==0)
// {


          Serial.print("AT+QIACT=1\r\n");
          sprintf(saveBuf + strlen(saveBuf), "%s,", "QIACT");
          // wait_for_at_response();
          time_out_cnt = 30000;
  waitForResponse();
          delay(100);
        #ifdef sDebug
          //Serial.flush();
        #endif
        

        
        
sprintf(stream_buffer_arr + strlen(stream_buffer_arr),"&lat=%s&lon=%s", "12.971600", "77.594600");

        
            
          //  sprintf(stream_buffer_arr + strlen(stream_buffer_arr), "\r\n");
          //-------------------------------- Kirti commented this to send real time data ------------------------------------------------------//
        
          char len[4];
          sprintf(len, "%d", strlen(stream_buffer_arr));
        
          char temp[25];
          for (int i = 0; i < 24; i++)
          {
            temp[i] = '\0';
          }
          
          sprintf(temp + strlen(temp), "AT+QHTTPURL=");
          sprintf(temp + strlen(temp), "%s", len);
          sprintf(temp + strlen(temp), ",30\r\n");
          Serial.flush();
          Serial.print(temp);
        //  sprintf(saveBuf + strlen(saveBuf), "%s,", "QHTTPURL");
        time_out_cnt = 30000;
  waitForResponse();
          // wait_for_at_response();
          delay(100);
        #ifdef sDebug
          //Serial.flush();
        #endif
        
          Serial.print(stream_buffer_arr);
          Serial.print("\r\n");
          // sprintf(saveBuf + strlen(saveBuf), "%s,", "buffer");
          // wait_for_at_response();
          time_out_cnt = 30000;
  waitForResponse();
          delay(100);
        #ifdef sDebug
          //Serial.flush();
        #endif
        
          //  Serial.begin(115200);
          Serial.flush();
          Serial.print("AT+QHTTPGET=30\r\n");
          sprintf(saveBuf + strlen(saveBuf), "%s,", "QHTTPGET");
          time_out_cnt = 12000;
          waitForResponse();
          wait_for_at_response();
          delay(100);
        
          //  Serial.flush();
        
   
}
void sendDataToServer()
{
  //  WiFi.mode(WIFI_AP_STA);
  enable4GSerial();
  delay(40);
//  ioCon2.digitalWrite(6, HIGH); //SetupEC200
//  ioCon2.digitalWrite(7, HIGH);
  Serial.flush();
//  Serial.begin(115200);
#ifdef newdebugPrint
  Serial.println("-------- sendDataToServer ---------");
#endif

  sprintf(stream_buffer_arr + strlen(stream_buffer_arr), "http://api.urbansciences.in:80/quartz/rawdata?");
  strcat(stream_buffer_arr, "&imei=");
  strcat(stream_buffer_arr, "C8C9A3929102");
  formSensorData();
sendDataEC200();

}


#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <PCA9554.h>  // Load the PCA9554 Library
#include "pca.h"
#include "pms.h"
#include "ec200.h"
// char stream_buffer_arr[650];
int value1 = 33, value2 = 44;
char saveBuf[200];
char imeiStr[15];
uint32_t startt = 0;

Cleaner Sweeper;


int atcount = 0;
// int16_t readADS1115(uint16_t config) {
//   // Step 1: Write config register
//   Wire.beginTransmission(ADS_ADDR);
//   Wire.write(0x01);           // Point to config register
//   Wire.write(config >> 8);    // MSB
//   Wire.write(config & 0xFF);  // LSB
//   Wire.endTransmission();

//   // Step 2: Wait for conversion (depends on data rate)
//   delay(10);

//   // Step 3: Read conversion register
//   Wire.beginTransmission(ADS_ADDR);
//   Wire.write(0x00);  // Point to conversion register
//   Wire.endTransmission();

//   Wire.requestFrom(ADS_ADDR, 2);
//   int16_t value = (Wire.read() << 8) | Wire.read();
//   return value;
// }


void setup() {

  pmsSerial.begin(9600);
  Serial.begin(115200);
  initPMS();
  Serial.println();
  Serial.println("PMS started...");
  Wire.begin();

  Serial.println("Begin...");

  init_pca_on_board_gpio();
  // read_io();
  // set_io();
  init_ec();  // it is not necessary

  delay(100);
  setup_ec();
  strcpy(imeiStr, "C8C9A3929102");
}



void loop() {

    //   atcount++;
    // Serial.print("attempt number: ");
    // Serial.println(atcount);

      read_io();
              while(millis()-startt>10000){
              startt = millis();
                  Sweeper.clear_stream_buff();
                  sendDataToServer();   
                  Sweeper.clear_stream_buff();

            }


    // switchop();
    // uint16_t config =
    //       0x8000 |  // OS = 1 (start conversion)
    //       0x7000 |  // MUX = AIN3
    //       0x0000 |  // PGA = ±4.096V
    //       0x0100 |  // MODE = single shot
    //       0x0080;   // 128 SPS

    //   int16_t adc = readADS1115(config);

    //   float voltage = (adc * 6.144) / 32768.0;

    //   Serial.print("ADC = ");
    //   Serial.print(adc);
    //   Serial.print("   Voltage = ");
    //   Serial.println(voltage);

    //   delay(500);

    // switchop();


    // readPMS();
    // Serial.println();


}

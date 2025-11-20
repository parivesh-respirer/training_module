#include "o3_sensor.h"
#include <Arduino.h>
#include "Wire.h"

int16_t readADS1115(uint16_t config) {
  // Step 1: Write config register
  Wire.beginTransmission(ADS_ADDR);
  Wire.write(0x01);           // Point to config register
  Wire.write(config >> 8);    // MSB
  Wire.write(config & 0xFF);  // LSB
  Wire.endTransmission();

  // Step 2: Wait for conversion (depends on data rate)
  delay(10);

  // Step 3: Read conversion register
  Wire.beginTransmission(ADS_ADDR);
  Wire.write(0x00);  // Point to conversion register
  Wire.endTransmission();

  Wire.requestFrom(ADS_ADDR, 2);
  int16_t value = (Wire.read() << 8) | Wire.read();
  return value;
}

float read_o3_op1(){
    uint16_t config =
          0x8000 |  // OS = 1 (start conversion)
          0x7000 |  // MUX = AIN3
          0x0000 |  // PGA = ±4.096V
          0x0100 |  // MODE = single shot
          0x0080;   // 128 SPS

      int16_t adc = readADS1115(config);

      float voltage = (adc * 6.144) / 32768.00;

      Serial.print("ADC = ");
      Serial.print(adc);
      Serial.print("   Voltage = ");
      Serial.println(voltage);
      
return voltage;
      // delay(500);
}
float read_o3_op2();
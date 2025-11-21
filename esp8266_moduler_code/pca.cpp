#include "pca.h"
#include "Arduino.h"


uint8_t mux_select;

void writeRegister(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(PCA9554_ADDR);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

uint8_t readRegister(uint8_t reg) {
  Wire.beginTransmission(PCA9554_ADDR);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(PCA9554_ADDR, 1);
  return Wire.read();
}
void writeRegister_ec(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(PCA9554_ADDRec);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

uint8_t readRegister_ec(uint8_t reg) {
  Wire.beginTransmission(PCA9554_ADDRec);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(PCA9554_ADDRec, 1);
  return Wire.read();
}


void init_pca_on_board_gpio() {
  writeRegister(REG_CONFIG, 0x07);
}

void read_io() {
  readRegister(REG_INPUT);
  byte rdata = 0xFF;
#define dip_addr 0x21

  // Wire.beginTransmission(dip_addr);
  // Wire.write((uint8_t)0);
  // Wire.endTransmission();

  // Wire.requestFrom(dip_addr, 1);

  if (Wire.available()) rdata = Wire.read();
  rdata = rdata & 0x06;
  //  Serial.println ("DIP: " + String(rdata, DEC));

  Serial.flush();
}

void set_io() {


  byte rdata = 0x00;

  if (mux_select == 0) {
    rdata = rdata + 0x00;  //Hcho

  } else if (mux_select == 1) {
    rdata = rdata + 0xC0;  //EC200

  } else if (mux_select == 2) {
    rdata = rdata + 0x40;  //


  } else if (mux_select == 3) {
    rdata = rdata + 0xC0;  //

  } else {
    rdata = rdata + 0xC0;  // default
  }
  //
  // writeRegister(REG_CONFIG, 0x00);
  writeRegister(REG_OUTPUT, rdata);

  delay(200);                 // allow mux to settle
  while (Serial.available())  // flush garbage
    Serial.read();
}


void enableUARTSerial() {
  mux_select = 3;
  set_io();
  //  Serial.begin(115200);
}
void enable4GSerial() {
  mux_select = 1;
  set_io();
  // Serial.begin(115200);
}

void switch_to_op2(){
    mux_select = 2;
  set_io();
}

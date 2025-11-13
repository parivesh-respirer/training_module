#include "pca.h"

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
#ifndef PCA_H
#define PCA_H

#include <Wire.h>

#define REG_INPUT 0x00
#define REG_OUTPUT 0x01
#define REG_POLARITY 0x02
#define REG_CONFIG 0x03

#define PCA9554_ADDRec 0x20
#define PCA9554_ADDR 0x21


void writeRegister(uint8_t reg, uint8_t value);

uint8_t readRegister(uint8_t reg);

void writeRegister_ec(uint8_t reg, uint8_t value); 

uint8_t readRegister_ec(uint8_t reg);


#endif
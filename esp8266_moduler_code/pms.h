#ifndef PMS_H
#define PMS_H

#include <Arduino.h>
#include <SoftwareSerial.h>

extern SoftwareSerial pmsSerial;

void initPMS();
void readPMS();
void make_pms_array_zero();
int16_t read_pm1_sensor_value();
int16_t read_pm25_sensor_value();
int16_t read_pm10_sensor_value();
#endif

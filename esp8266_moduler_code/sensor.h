#ifndef SENSOR_H
#define SENSOR_H

#include "pms.h"

extern char stream_buffer_arr[650];
void formSensorData();
int16_t readADS1115(uint16_t config);
#endif
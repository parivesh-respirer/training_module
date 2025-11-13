#ifndef PMS_H
#define PMS_H

#include <Arduino.h>
#include <SoftwareSerial.h>

extern SoftwareSerial pmsSerial;

void initPMS();
void readPMS();

#endif

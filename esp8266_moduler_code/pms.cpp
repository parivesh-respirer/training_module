#include "pms.h"
#include "pca.h"

#define number_of_samples 5

SoftwareSerial pmsSerial(0, 2);  // RX, TX
int16_t pm_sensor_value[32];
int16_t prev_pm1_atm = 0;
int16_t prev_pm25_atm = 0;
int16_t prev_pm10_atm = 0;

void initPMS() {
  pmsSerial.begin(9600);
}


void make_pms_array_zero() {
  for (int i = 0; i < 32; i++) {
    pm_sensor_value[i] = 0;
  }
}
void readPMS(void) {

if (pmsSerial.read() != 0x42) return;

  // Wait for second header byte
  while (!pmsSerial.available());
  if (pmsSerial.read() != 0x4D) return;

  // Read 30 remaining bytes
  for (int i = 0; i < 30; i++) {
    while (!pmsSerial.available());
    pm_sensor_value[i] = pmsSerial.read();
  }
}

  // // Need 32 bytes to read full frame
  // while (pmsSerial.available()) {
  //   // Look for first header byte 0x42
  //   if (pmsSerial.read() != 0x42) {
  //     continue;  // skip until 0x42 found
  //   }

  //   // Wait for next byte
  //   while (!pmsSerial.available())
  //     ;

  //   // Check second header byte 0x4D
  //   if (pmsSerial.read() != 0x4D) {
  //     continue;  // wrong second byte, restart search
  //   }

  //   // Now read remaining 30 bytes safely
  //   for (int i = 0; i < 30; i++) {
  //     while (!pmsSerial.available());        
  //     pm_sensor_value[i] = pmsSerial.read();
  //   }

  //   // Frame is valid → stop
  //   // return;
//   }
// }

int16_t read_pm1_sensor_value() {
  //   readPMS();
  int16_t pm1 = (pm_sensor_value[8] << 8) | pm_sensor_value[9];
  Serial.print("PM1: ");
  Serial.println(pm1);
  
  return pm1;
}


int16_t read_pm25_sensor_value() {
  //   readPMS();
  int16_t pm25 = (pm_sensor_value[10] << 8) | pm_sensor_value[11];
  Serial.print("PM2.5: ");
  Serial.println(pm25);
  return pm25;
}


int16_t read_pm10_sensor_value() {
  //   readPMS();
  int16_t pm10 = (pm_sensor_value[12] << 8) | pm_sensor_value[13];
  Serial.print("PM10: ");
  Serial.println(pm10);
  return pm10;
}

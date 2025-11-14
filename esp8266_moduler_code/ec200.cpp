#include "ec200.h"
#include <Arduino.h>
#include "pca.h"

void wait_for_at_response(void) {
  uint32_t timeOut = 3000, timer = millis();  // increased timeout for slow responses
  char temp[200];
  int i = 0;

  // Wait for response or timeout
  while ((millis() - timer < timeOut)) {
    if (Serial.available()) {
      char c = Serial.read();
      if (i < sizeof(temp) - 1) {
        temp[i++] = c;
      }
      delay(1);
    }
  }

  // Terminate string to prevent garbage print
  temp[i] = '\0';

  // Filter out unreadable characters
  Serial.print("data is: ");
  for (int j = 0; j < i; j++) {
    if (isPrintable(temp[j]) || temp[j] == '\r' || temp[j] == '\n') {
      Serial.print(temp[j]);
    }
  }
  Serial.println();
}



void setup_ec(void) {
  enable4GSerial();
  writeRegister(REG_CONFIG, 0x07);


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
}

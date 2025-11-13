#include "pms.h"

SoftwareSerial pmsSerial(0, 2);   // RX, TX

void initPMS() {
    pmsSerial.begin(9600);
}

void readPMS() {
    while (pmsSerial.available()) {
        uint8_t c = pmsSerial.read();
        Serial.print(c, HEX);
        Serial.print(" ");
    }
}

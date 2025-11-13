#include <Arduino.h>
// #include <Wire.h>
#include <SoftwareSerial.h>
#include <PCA9554.h>  // Load the PCA9554 Library
#include "pca.h"
#include "pms.h"

// int RX=0,TX=2;
// SoftwareSerial pmsSerial(RX, TX);
// PCA9554 ioCon1(0x20);  // Create an object at this address   P6,P7 select pins on board P6 charge and P7 standby P6,P7 high 1
// PCA9554 ioCon2(0x21);  // Create an object at this address
unsigned long start = 0;
unsigned long start1 = 0;
unsigned long prevMillis = 0;
const unsigned long interval = 2000;  // 5 seconds
int toggle = 0;
uint8_t mux_select;
uint32_t time_out_cnt;
byte timeout_flg;
bool EC200Flag;
char CTZRResponse[100];
bool timeFlag;
int  atcount = 0;
byte reset_count = 20;
byte serial_failure_count = 0;
#define SERIAL_FAILURE_RESTART_CT 50

void wait(void) {
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

void set_io() {


  byte rdata = 0x00;

  if (mux_select == 0) {
    rdata = rdata + 0x00;  //Hcho

  } else if (mux_select == 1) {
    rdata = rdata + 0x40;  //EC200

  } else if (mux_select == 2) {
    rdata = rdata + 0x80;  //


  } else if (mux_select == 3) {
    rdata = rdata + 0xC0;  //

  } else {
    rdata = rdata + 0xC0;  // default
  }
  //
  writeRegister(REG_OUTPUT, rdata);
  //   #define dip_addr 0x21
  //     Wire.beginTransmission(dip_addr);
  //     Wire.write((uint8_t)1);
  //     Wire.write((uint8_t)rdata);
  //     Wire.endTransmission();
  //     Serial.println(rdata);
  delay(200);                       // allow mux to settle
while (Serial.available())       // flush garbage
  Serial.read();
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
void setup_io() {
  writeRegister(REG_CONFIG, 0x07);
  // ioCon2.pinMode(0, INPUT);   //ENB_5_EXT
  // ioCon2.pinMode(1, INPUT);   //EXT_5_AVL
  // ioCon2.pinMode(2, INPUT);   //SOLAR_AVL
  // ioCon2.pinMode(3, OUTPUT);  //ENB_SOLAR
  // ioCon2.pinMode(4, OUTPUT);  //LED_GREEN
  // ioCon2.pinMode(5, OUTPUT);  //LED_RED
  // ioCon2.pinMode(6, OUTPUT);  //CHARGE
  // ioCon2.pinMode(7, OUTPUT);  //STDBY
}

void setup() {

// pmsSerial.begin(9600);
  Serial.begin(115200);
   initPMS();
    Serial.println("PMS started...");


  Serial.println("Begin...");
  Wire.begin();
  setup_io();
  read_io();
  // set_io();
  delay(100);
  setup_ec();
}

void loop() {

 readPMS();

  //   while (pmsSerial.available()) {
  //   uint8_t c = pmsSerial.read();
  //   Serial.print(c, HEX);
  //   Serial.print(" ");
  // }
     atcount++;
   Serial.print("attempt number: ");
   Serial.println(atcount);
  read_io();
      
while (Serial.available()) Serial.read();
  Serial.print("ATI\r\n");
  delay(100);
  wait();
  delay(1000);

  // Serial.print("AT+QHTTPCFG=\"contextid\",1\r\n");
  while (Serial.available()) Serial.read();
  Serial.print("ATE0\r\n");
  delay(100);
  wait();
  delay(1000);

  //   Serial.print("AT+QHTTPCFG=\"responseheader\",1\r\n");
  //   delay(100);
  //   wait();
  //   delay(500);
}

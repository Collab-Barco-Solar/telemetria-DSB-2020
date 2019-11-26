// Feito para o NODE-MCU
#include <HardwareSerial.h>

HardwareSerial serial_sd(2); // Try to change this (2)


#define BAUD 300
#define SD_BAUD 300
#define TXPin 1
#define RXPin 3

void setup() {

  Serial.begin(BAUD);

}

void loop() {

  long n;
  n = Serial.read();
  Serial.println(n);
  //Serial.swap();
}

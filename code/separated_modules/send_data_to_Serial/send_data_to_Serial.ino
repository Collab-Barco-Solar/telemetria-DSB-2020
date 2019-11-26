// Feito para o ESP32 LOLIN32
#include <HardwareSerial.h>

HardwareSerial serial_sd(2); // Try to change this (2)

#define BAUD 300
#define SD_BAUD 300

void setup() {
  
  Serial.begin(BAUD);
  Serial2.begin(SD_BAUD);

}

void loop() {

  randomSeed(42);

  int r = 0;
  r = random(0,12);
  
  Serial2.write(r);
  Serial.println(r);

  delay(100);
}

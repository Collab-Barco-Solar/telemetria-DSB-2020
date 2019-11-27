/*
  SD card datalogger

  Example running on the ESP32 and requiring 5V at the SD card reader VCC ( CATALEX READER )
*/

#include <SPI.h>
#include <SD.h>

const int chipSelect = 5;

void setup() {

  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
    
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    while(1);
  }
  Serial.println("card initialized.");
}

void loop() {
  
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println("12");
    dataFile.close();
    // print to the serial port too:
    Serial.println("12");
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }

  delay(100);
}

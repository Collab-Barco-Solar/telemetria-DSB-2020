#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>

#define RXPin    15  // Neo6M RX pin
#define TXPin    12  // Neo6M TX pin
#define GPSBaud 9600 // Neo6M Baud rate
#define BAUD 2000000  // BAUD serial rate


TinyGPSPlus gps;      // GPS object
HardwareSerial ss(2); // Hardware Serial comunication object

static const double CONVENTO_LAT = -20.327972, CONVENTO_LON = -40.287203;

void setup() {

  
  Serial.begin(BAUD);
  ss.begin(GPSBaud, SERIAL_8N1, TXPin, RXPin);

  
}

void loop() {
  
  unsigned long distanceKmToTest =
    (unsigned long)TinyGPSPlus::distanceBetween(
      gps.location.lat(),
      gps.location.lng(),
      CONVENTO_LAT, CONVENTO_LON) / 1000;
  Serial.println("Distance = " + distanceKmToTest);

//  while (ss.available() > 0){
//   Serial.write(ss.read());
//  }

}

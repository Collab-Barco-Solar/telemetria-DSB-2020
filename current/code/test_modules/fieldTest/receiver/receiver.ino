#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>  

#define SCK     5     // GPIO5  -- SX1278's SCK
#define MISO    19    // GPIO19 -- SX1278's MISO
#define MOSI    27    // GPIO27 -- SX1278's MOSI
#define SS      18    // GPIO18 -- SX1278's CS
#define RST     14    // GPIO14 -- SX1278's RESET
#define DI0     26    // GPIO26 -- SX1278's IRQ(Interrupt Request)
#define FREQ  915E6   // Operating LoRa frequency
#define SF      12     // Operating LoRa Spread Factor
#define BAND  125E3   // Operating LoRa Bandwidth
#define BAUD 2000000  // BAUD serial rate

String rssi = "RSSI --";
String packSize = "--";
String packet ;


void cbk(int packetSize) {
  packet ="";
  for (int i = 0; i < packetSize; i++) { packet += (char) LoRa.read(); }
  rssi = String(LoRa.packetRssi(), DEC) ;
  
  Serial.print( rssi + ";" );
  Serial.println( packet );
}

void setup() {
  
  Serial.begin(BAUD);
  while (!Serial);
  Serial.println();
  Serial.println("LoRa Receiver Callback");
  SPI.begin(SCK,MISO,MOSI,SS);
  LoRa.setPins(SS,RST,DI0);  
  if (!LoRa.begin(FREQ)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  LoRa.setSpreadingFactor(SF);
  LoRa.setSignalBandwidth(BAND);
  LoRa.enableCrc();
  
  //LoRa.onReceive(cbk);
  LoRa.receive();
  Serial.println("RSSI ; Latitude, Longitude ; Date ; Time ");

  delay(1000);
  
}


void loop() {
  int packetSize = LoRa.parsePacket();
  
  if (packetSize) { 
    cbk(packetSize);
  }

  
  delay(10);
  
}

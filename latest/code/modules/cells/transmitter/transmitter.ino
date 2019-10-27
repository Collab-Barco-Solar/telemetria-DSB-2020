#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>  


#define SCK     5     // GPIO5  -- SX1278's SCK
#define MISO    19    // GPIO19 -- SX1278's MISnO
#define MOSI    27    // GPIO27 -- SX1278's MOSI
#define SS      18    // GPIO18 -- SX1278's CS
#define RST     14    // GPIO14 -- SX1278's RESET
#define DI0     26    // GPIO26 -- SX1278's IRQ(Interrupt Request)

#define FREQ  915E6   // Operating LoRa frequency
#define SF      12    // Operating LoRa Spread Factor
#define BAND  125E3   // Operating LoRa Bandwidth
#define TXPOWER 20    // Operating LoRa Transmition Power
#define BAUD 2000000  // BAUD serial rate

unsigned int counter = 0;

String rssi = "RSSI --";
String packSize = "--";
String packet ;

 

void setup() {
  
  Serial.begin(BAUD);
  while (!Serial);
  Serial.println();
  Serial.println("LoRa Sender Test");
  
  SPI.begin(SCK,MISO,MOSI,SS); 
  LoRa.setPins(SS,RST,DI0);
  if (!LoRa.begin(FREQ)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  LoRa.setSpreadingFactor(SF);
  LoRa.setSignalBandwidth(BAND);
  LoRa.setTxPower(TXPOWER);
  LoRa.enableCrc();
  
  //LoRa.onReceive(cbk);
  //  LoRa.receive();
  Serial.println("Initialization: ok");
 
  delay(1500);
}

void loop() {
  String message = "SisTel";
  //Display counter and analog value in serial monitor
  Serial.println( String(counter) + " " + message);
  
  // Create and send packet
  LoRa.beginPacket();
  LoRa.print(message);  
  LoRa.print(" ");
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;
  //delay(50);
}

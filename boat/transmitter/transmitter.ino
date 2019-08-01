// bibliotecas

#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>


//pinos

#define SCK     5     // GPIO5  -- LoRa SX1278's SCK
#define MISO    19    // GPIO19 -- LoRa SX1278's MISnO
#define MOSI    27    // GPIO27 -- LoRa SX1278's MOSI
#define SS      18    // GPIO18 -- LoRa SX1278's CS
#define RST     14    // GPIO14 -- LoRa SX1278's RESET
#define DI0     26    // GPIO26 -- LoRa SX1278's IRQ(Interrupt Request)

#define RXPin    15  // Neo6M RX pin
#define TXPin    12  // Neo6M TX pin
#define GPSBaud 9600 // Neo6M Baud rate


//defines

#define FREQ  915E6   // Operating LoRa frequency
#define SF      7    // Operating LoRa Spread Factor
#define BAND  125E3   // Operating LoRa Bandwidth
#define TXPOWER 20    // Operating LoRa Transmition Power
#define BAUD 2000000  // BAUD serial rate

//objetos

String rssi = "RSSI --";
String packSize = "--";
String packet ;

TinyGPSPlus gps;      // GPS object
HardwareSerial ss(2); // Hardware Serial comunication object
//falta o ads


//setup

//functions

String LatitudeGPS( TinyGPSPlus gps ){
  return "To Implement";
  /* 
   while (ss.available() > 0)
    if (gps.encode(ss.read())){
      if (gps.location.isValid()){
        
        LoRa.print(gps.location.lat(), 6);
        LoRa.print(F(","));
        LoRa.print(gps.location.lng(), 6);
        csvSeparator();
      }
      else{
        GPSerrorMessage();
        Serial.print("Invalid location");
      }
      */
}

String LongitudeGPS( TinyGPSPlus gps ){
  return "To Implement";
}

char CSV_Separator(){
  return (";");
}

void setup() {
  
  Serial.begin(BAUD);
  ss.begin(GPSBaud, SERIAL_8N1, TXPin, RXPin); // GPS serial communication
  
  while (!Serial);
  Serial.println();
  Serial.println("Boat sender");
  
  SPI.begin(SCK,MISO,MOSI,SS); // LoRa SPI communication
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
  
  // Create and send packet
  LoRa.beginPacket();
  // Escrever localizacao
  LoRa.print(LatitudeGPS(gps));
  LoRa.print(CSV_Separator());
  LoRa.print(LongitudeGPS(gps));
  LoRa.print(CSV_Separator());
  // Escrever o valor no shunt 

  
  //LoRa.print(counter);
  LoRa.endPacket();

  counter++;
  //delay(50);
}

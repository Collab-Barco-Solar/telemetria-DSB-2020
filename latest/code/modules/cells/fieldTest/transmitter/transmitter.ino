#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>


#define SCK     5     // GPIO5  -- SX1278's SCK
#define MISO    19    // GPIO19 -- SX1278's MISnO
#define MOSI    27    // GPIO27 -- SX1278's MOSI
#define SS      18    // GPIO18 -- SX1278's CS
#define RST     14    // GPIO14 -- SX1278's RESET
#define DI0     26    // GPIO26 -- SX1278's IRQ(Interrupt Request)

#define RXPin    15  // Neo6M RX pin
#define TXPin    12  // Neo6M TX pin
#define GPSBaud 9600 // Neo6M Baud rate

#define FREQ  915E6   // Operating LoRa frequency
#define SF      7    // Operating LoRa Spread Factor
#define BAND  125E3   // Operating LoRa Bandwidth
#define TXPOWER 20    // Operating LoRa Transmition Power
#define BAUD 2000000  // BAUD serial rate

unsigned int counter = 0;

String rssi = "RSSI --";
String packSize = "--";
String packet ;

TinyGPSPlus gps;      // GPS object
HardwareSerial ss(2); // Hardware Serial comunication object

void setup() {
  
  Serial.begin(BAUD);
  ss.begin(GPSBaud, SERIAL_8N1, TXPin, RXPin);
  
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

void csvSeparator(){
  LoRa.print(F(";"));
}

void GPSerrorMessage(){
  LoRa.print(F("*"));
  csvSeparator();
}

void loop() {
  String message = "SisTel";
  //Display counter and analog value in serial monitor
  Serial.println( String(counter) + " " + message);
  
  // Create and send packet
  LoRa.beginPacket();
  // Enviar localizacao
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

      if (gps.date.isValid()){
        LoRa.print(gps.date.month());
        LoRa.print(F("/"));
        LoRa.print(gps.date.day());
        LoRa.print(F("/"));
        LoRa.print(gps.date.year());
        csvSeparator();
      }
      else{
        GPSerrorMessage();
        Serial.print("Invalid date");
      }
    
      Serial.print(F(" "));
      if (gps.time.isValid()){
        if (gps.time.hour() < 10) LoRa.print(F("0"));
        LoRa.print(gps.time.hour());
        LoRa.print(F(":"));
        if (gps.time.minute() < 10) LoRa.print(F("0"));
        LoRa.print(gps.time.minute());
        LoRa.print(F(":"));
        if (gps.time.second() < 10) LoRa.print(F("0"));
        LoRa.print(gps.time.second());
        LoRa.print(F("."));
        if (gps.time.centisecond() < 10) LoRa.print(F("0"));
        LoRa.print(gps.time.centisecond());
        break;
      }
      else
      {
        GPSerrorMessage();
        Serial.print("Invalid time");
      }

    }
  // 

  
  //LoRa.print(counter);
  LoRa.endPacket();

  counter++;
  //delay(50);
}

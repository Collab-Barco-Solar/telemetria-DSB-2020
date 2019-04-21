#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>  


#define SCK     5    // GPIO5  -- SX1278's SCK
#define MISO    19   // GPIO19 -- SX1278's MISnO
#define MOSI    27   // GPIO27 -- SX1278's MOSI
#define SS      18   // GPIO18 -- SX1278's CS
#define RST     14   // GPIO14 -- SX1278's RESET
#define DI0     26   // GPIO26 -- SX1278's IRQ(Interrupt Request)
#define BAND  915E6
#define BAUD 9600 // baud serial rate

unsigned int counter = 0;

String rssi = "RSSI --";
String packSize = "--";
String packet ;

 

void setup() {
  pinMode(16,OUTPUT); //oled
  pinMode(2,OUTPUT);
  
  
  Serial.begin(BAUD);
  while (!Serial);
  Serial.println();
  Serial.println("LoRa Sender Test");
  
  SPI.begin(SCK,MISO,MOSI,SS);
  LoRa.setPins(SS,RST,DI0);
  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  //LoRa.onReceive(cbk);
//  LoRa.receive();
  Serial.println("init ok");
 // colocar escrita serial
 
  delay(1500);
}

void loop() {

  //mostra valor
  Serial.println(String(counter));


  
  // send packet
  LoRa.beginPacket();
  LoRa.print("Telemetria esta avancando> ");
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;
  digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(2, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}

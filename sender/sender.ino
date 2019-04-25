#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>  


#define SCK     5     // GPIO5  -- SX1278's SCK
#define MISO    19    // GPIO19 -- SX1278's MISnO
#define MOSI    27    // GPIO27 -- SX1278's MOSI
#define SS      18    // GPIO18 -- SX1278's CS
#define RST     14    // GPIO14 -- SX1278's RESET
#define DI0     26    // GPIO26 -- SX1278's IRQ(Interrupt Request)
#define ANALOG_PIN 36 // GPIO36 -- Analog input
#define BAND  915E6   // Operating LoRa frequency
#define BAUD 2000000  // BAUD serial rate

unsigned int counter = 0;

String rssi = "RSSI --";
String packSize = "--";
String packet ;

 

void setup() {
  pinMode(16,OUTPUT); //oled
  pinMode(2,OUTPUT);
  pinMode(ANALOG_PIN, INPUT);
  
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
 
  delay(1500);
}

void loop() {

  double voltage = analogRead(ANALOG_PIN); // Analog voltage measured

  //Display counter and analog value in serial monitor
  Serial.print(String(counter));
  Serial.println("  tensao> " + String(voltage)); 
  
  // Create and send packet
  LoRa.beginPacket();
  LoRa.print("Contador e tensão> ");
  LoRa.print(counter);
  LoRa.print(" ; ");
  LoRa.print(voltage);
  LoRa.endPacket();

  counter++;
}

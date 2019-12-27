#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>  

#define SCK     5     // GPIO5  -- SX1278's SCK
#define MISO    19    // GPIO19 -- SX1278's MISnO
#define MOSI    27    // GPIO27 -- SX1278's MOSI
#define SS      18    // GPIO18 -- SX1278's CS
#define RST     14    // GPIO14 -- SX1278's RESET
#define DI0     26    // GPIO26 -- SX1278's IRQ(Interrupt Request)
#define ANALOG_PIN 13 // GPIO36 -- Analog input
#define BAND  915E6   // Operating LoRa frequency
#define BAUD 2000000  // BAUD serial rate
#define RATIO 3.3/4096// Conversion rate 

double measure, voltage;
unsigned int counter = 0;
String rssi = "RSSI --";
String packSize = "--";
String packet ;


void setup() {
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
  
  Serial.println("init ok");
 
  delay(1500);
}

void loop() {
  
	measure = analogRead(ANALOG_PIN);
	voltage = measure * RATIO;
	Serial.print("Voltage: ");
  Serial.print(voltage, 8);
  Serial.print(" ");
  Serial.print("Measure: ");
  Serial.print(measure);
  Serial.print(" ");
  Serial.print("Counter: ");
  Serial.println(counter);

  LoRa.beginPacket();
  LoRa.print(" ");
  LoRa.print("Voltage: ");
  LoRa.print(voltage, 8);
  LoRa.print(" ; Measure: ");
  LoRa.print(measure);
  LoRa.print(" ; Counter: ");
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;
  delay(50);
  
}

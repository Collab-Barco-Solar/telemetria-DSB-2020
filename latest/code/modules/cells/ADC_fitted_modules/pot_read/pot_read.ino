// bibliotecas

#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <Adafruit_ADS1015.h>

//Transmission used pins

#define SCK     5     // GPIO5  -- LoRa SX1278's SCK
#define MISO    19    // GPIO19 -- LoRa SX1278's MISnO
#define MOSI    27    // GPIO27 -- LoRa SX1278's MOSI
#define SS      18    // GPIO18 -- LoRa SX1278's CS
#define RST     14    // GPIO14 -- LoRa SX1278's RESET
#define DI0     26    // GPIO26 -- LoRa SX1278's IRQ(Interrupt Request)

#define RXPin    15  // Neo6M RX pin
#define TXPin    12  // Neo6M TX pin
#define GPSBaud 9600 // Neo6M Baud rate

#define BAUD 2000000  // BAUD serial rate

//MUX control pins

#define S0 32 //MUX control pins
#define S1 14
#define S2 13
#define S3 0
#define MUX_SIG 4 //MUX input Pin

// polynomial coefficients

#define   p5 17.5938359490609
#define   p4  1.21697808640912 
#define   p3  -0.000168313273959029
#define   p2  7.69758075646963e-08
#define   p1  -1.21956845031952e-1

const float DT5_RATIO = 1.552971576f; // VOLTAGE DIVIDER FOR THE POTENTIOMETER1 

// MUX input pins

 const byte DMSMux = 0;
 const byte ReverseMux = 1;
 const byte OnOffMux = 2;
 const byte CruiseMux = 3;
 const byte PotMux = 4;
 const byte CBMux = 5;
 const byte BBMux = 6;
 const byte BEMux = 7;
 const byte CEMux = 8;
 const byte ACS1Mux = 9;
 const byte BatAMux = 10;
 const byte PhotoMux = 11;
 const byte BatBankMux = 12;
 const byte ACS2Mux = 13;

// Function declaration and method
float polyfit(byte value){
  float fittedReading;  
  fittedReading = (value*value*value*value*p1)+(value*value*value*p2)+(value*value*p3) + (value*p4) + p5;
  return fittedReading;
}

float PotentiometerRead(){
  
  SetMuxChannel(PotMux);
  float readVoltage = (polyfit(analogRead(MUX_SIG)) * 3.3) / 4095;  //if analog read == 4095, it is reading 3.3V, so convert the reading from bits to Voltage
  
  return readVoltage * DT5_RATIO * 2; //Multiply by the ratio of the voltage divider to find the true voltage value
}

void SetMuxChannel (byte channel) {
  
  digitalWrite(S0, channel>>0&1);
  digitalWrite(S1, channel>>1&1);
  digitalWrite(S2, channel>>2&1);
  digitalWrite(S3, channel>>3&1); 
  delay(10);

}

void setup() {
  
  Serial.begin(BAUD);
  /*
  ss.begin(GPSBaud, SERIAL_8N1, TXPin, RXPin); // GPS serial communication
  */
  //pinMode(PIN_POTENCIOMETER, INPUT);
  //MUX pins
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(MUX_SIG, INPUT);

  digitalWrite(S0, LOW);
  digitalWrite(S1, LOW);
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  
  /*
  while (!Serial);
  Serial.println();
  Serial.println("Boat sender");
  
  SPI.begin(SCK,MISO,MOSI,SS); // LoRa SPI communication
  LoRa.setPins(SS,RST,DI0);
  
  if (!LoRa.begin(FREQ)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  */
  Serial.println("Initialization: ok");
 
  delay(1500);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Pot: ");
  Serial.println(PotentiometerRead());
  delay(50);
}

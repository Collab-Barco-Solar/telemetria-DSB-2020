// bibliotecas

#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <Adafruit_ADS1015.h>

// General defines

#define BAUD 2000000  // BAUD serial rate

// Mux defines

#define S0 32 //MUX control pins
#define S1 14
#define S2 13
#define S3 0
#define MUX_EN 33 //MUX pin to turn on and off
#define MUX_SIG 4 //MUX input Pin

// polynomial coefficients

#define   p5 17.5938359490609
#define   p4  1.21697808640912 
#define   p3  -0.000168313273959029
#define   p2  7.69758075646963e-08
#define   p1  -1.21956845031952e-11 

//Conversion Ratios (Voltage Divider)

float DT1_RATIO = 19.333333333f;
float DT2_RATIO = 4.970588235f;
float DT3_RATIO = 28.5f;
float DT4_RATIO = 1.564102564f;
float DT5_RATIO = 1.552971576f; // VOLTAGE DIVIDER FOR THE POTENTIOMETER
// MUX input pins

 const int DMSMux = 0;
 const int ReverseMux = 1;
 const int OnOffMux = 2;
 const int CruiseMux = 3;
 const int PotMux = 4;
 const int CBMux = 5;
 const int BBMux = 6;
 const int BEMux = 7;
 const int CEMux = 8;
 const int ACS1Mux = 9;
 const int BatAMux = 10;
 const int PhotoMux = 11;
 const int BatBankMux = 12;
 const int ACS2Mux = 13;


// Functions

float polyfit(int value)
{
  float fittedReading;  
  fittedReading = (value*value*value*value*p1)+(value*value*value*p2)+(value*value*p3) + (value*p4) + p5;
  return fittedReading;
}

float PotentiometerRead(){
  SetMuxChannel(PotMux);
  float readVoltage = (polyfit(analogRead(MUX_SIG)) * 3.3) / 4095;  //if analog read == 4095, it is reading 3.3V, so convert the reading from bits to Voltage
  
  return readVoltage * DT5_RATIO * 2; //Multiply by the ratio of the voltage divider to find the true voltage value
}

void SetMuxChannel ( int channel ) {
  
  digitalWrite(S0, channel>>0&1);
  digitalWrite(S1, channel>>1&1);
  digitalWrite(S2, channel>>2&1);
  digitalWrite(S3, channel>>3&1); 
  delay(10);

}

char CSV_Separator(){
  return (' ; ');
}


void setup()
{
    //pinMode(PIN_POTENCIOMETER, INPUT);
  //MUX pins
  Serial.begin(BAUD);
  Serial.println("Test code for the multiplexer");
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(MUX_SIG, INPUT);

  digitalWrite(S0, LOW);
  digitalWrite(S1, LOW);
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  delay(1000);
}

void loop()
{\


  Serial.print("PORTA: ");
  Serial.print(PotMux);
  Serial.print(" \t ");
  float readVoltage = PotentiometerRead();
  Serial.print(" TENSÃO: ");
  Serial.println(readVoltage);
    
  
  delay(500);
}

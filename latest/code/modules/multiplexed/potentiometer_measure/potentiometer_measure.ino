// bibliotecas

#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <Adafruit_ADS1015.h>

// Serial defines

#define BAUD 2000000            // BAUD serial rate

// Mux defines

#define S0 32 //MUX control pins
#define S1 14
#define S2 13
#define S3 0
#define MUX_SIG 4 //MUX input Pin

// polynomial coefficients

const float p5 = 17.5938359490609;
const float p4 = 1.21697808640912;
const float p3 = -0.000168313273959029;
const float p2 =  7.69758075646963e-08;
const float p1 = -1.21956845031952e-11;

// inc

int i = 0;

//Conversion Ratios (Voltage Divider)
const float DT5_RATIO = 1.552971576; // VOLTAGE DIVIDER FOR THE POTENTIOMETER

// MUX input pins
const byte PotMux = 4;

// Functions
float polyfit(float value)
{
  float fittedReading;  
  fittedReading = (value*value*value*value*p1)+(value*value*value*p2)+(value*value*p3) + (value*p4) + p5;
  Serial.print("Valor Ajustado: ");
  Serial.print(fittedReading);
  Serial.print(" \t ");
  
  return fittedReading;
}

float PotentiometerRead(){
  SetMuxChannel(PotMux);
  float readVoltage = (polyfit(analogRead(MUX_SIG)) * 3.3) / 4095;  //if analog read == 4095, it is reading 3.3V, so convert the reading from bits to Voltage
  return readVoltage; //Multiply by the ratio of the voltage divider to find the true voltage value
}

void SetMuxChannel ( int channel ) {
  
  digitalWrite(S0, channel>>0&1);
  digitalWrite(S1, channel>>1&1);
  digitalWrite(S2, channel>>2&1);
  digitalWrite(S3, channel>>3&1); 
  
}


void setup() {

  //pinMode(PIN_POTENCIOMETER, INPUT);
  //MUX pins
  Serial.begin(BAUD);
  Serial.println("Test code for the potentiometer multiplexed");
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
  
  

void loop() {

     
  Serial.print("Analog value:");
  Serial.print(analogRead(MUX_SIG));
  Serial.print(" \t ");
  int timeStarted = micros();
  float readVoltage = PotentiometerRead();
  int timeEnded = micros();
  Serial.print("T.Calc: ");
  Serial.print(timeEnded - timeStarted);
  Serial.print(" \t ");
  Serial.print(" TENSÃO: ");
  Serial.println(readVoltage);
  delay(10);

  delay(200);
  
}

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
#define S1 35
#define S2 34
#define S3 0
#define MUX_EN 33 //MUX pin to turn on and off
#define MUX_SIG 4 //MUX input Pin

//Conversion Ratios (Voltage Divider)

float DT1_RATIO = 19.333333333f;
float DT2_RATIO = 4.970588235f;
float DT3_RATIO = 28.5f;
float DT4_RATIO = 1.564102564f;

int MUX_CH[16][4] = {(0,0,0,0), //Channel 0
                     (1,0,0,0), //Channel 1
                     (0,1,0,0), //Channel 2
                     (1,1,0,0), //Channel 3
                     (0,0,1,0), //Channel 4
                     (1,0,1,0), //Channel 5
                     (0,1,1,0), //Channel 6
                     (1,1,1,0), //Channel 7
                     (0,0,0,1), //Channel 8
                     (1,0,0,1), //Channel 9
                     (0,1,0,1), //Channel 10
                     (1,1,0,1), //Channel 11
                     (0,0,1,1), //Channel 12
                     (1,0,1,1), //Channel 13
                     (0,1,1,1), //Channel 14
                     (1,1,1,1)}; //Channel 15


// Functions

void SetMuxChannel(int ChannelOrder[]){
  digitalWrite(S0, ChannelOrder[0]);
  digitalWrite(S1, ChannelOrder[1]);
  digitalWrite(S2, ChannelOrder[2]);
  digitalWrite(S3, ChannelOrder[3]);
}

float PotentiometerRead(){
  SetMuxChannel(MUX_CH[4]);
  float readVoltage = (analogRead(MUX_SIG) * 3.3) / 1024;  //if analog read == 1024, it is reading 3.3V, so convert the reading from bits to Voltage
  
  return readVoltage * DT4_RATIO * 2; //Multiply by the ratio of the voltage divider to find the true voltage value
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
  pinMode(MUX_EN, OUTPUT);
  pinMode(MUX_SIG, INPUT);

  digitalWrite(S0, LOW);
  digitalWrite(S1, HIGH);
  digitalWrite(S2, HIGH);
  digitalWrite(S3, LOW);
  digitalWrite(MUX_EN,LOW);
  delay(1000);
}

void loop()
{

  Serial.print("Potentiometer: ");
  //Serial.println(PotentiometerRead());


  delay(50);
}

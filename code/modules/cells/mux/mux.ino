#include <Wire.h>

#define   BAUD 2000000

#define S0 32 //MUX control pins
#define S1 13
#define S2 14
#define S3 0
#define MUX_EN 33 //MUX pin to turn on and off
#define MUX_SIG 4 //MUX input Pin

void changeMUX ( int channel ) {
  
  digitalWrite(S0, channel>>0&1);
  digitalWrite(S1, channel>>1&1);
  digitalWrite(S2, channel>>2&1);
  digitalWrite(S3, channel>>3&1); 
  
  
  //Serial.print(channel>>0&1);
  //Serial.print(channel>>1&1);
  //Serial.print(channel>>2&1);
  //Serial.print(channel>>3&1);
  //Serial.print(" \t ");
  
}

void setup(void) {

  Serial.begin(BAUD);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  pinMode(MUX_EN, OUTPUT);
  digitalWrite(MUX_EN, LOW);
  
  pinMode(MUX_SIG, INPUT);
  
  while (!Serial);

}


void loop(void) {
  
  for (int i=0 ; i < 16 ; i++){
    changeMUX(i);
    
    float sinal = analogRead(MUX_SIG)   *3.3/4096;  // Type needs to be adjusted
    
    Serial.print(i);
    Serial.print(":\t");
    Serial.println(sinal, 5);
  }
  
  delay(500);
  
}

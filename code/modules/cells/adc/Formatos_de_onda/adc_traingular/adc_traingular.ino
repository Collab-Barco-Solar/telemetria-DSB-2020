#include <Wire.h>

#define   ADC_12BIT_MAX   4096
#define   BAUD 2000000
#define   pin 4
#define   DAC1 25
#define   dacNormPrecision 0.0039215686274509803921568627451  

int logicLevelADC;
float voltageADC;
double i = 0;
double inc = 0;

void setup() {
  Serial.begin(BAUD);
  pinMode(pin, INPUT);
  /* aguarda a serial estar disponível */
  while (!Serial);
  Serial.println();  
}



void loop() {
  
    i >= 1 ? inc = -dacNormPrecision : 1;
    i <= 0 ? inc = dacNormPrecision : 1;
    dacWrite( DAC1 , i*255 );
    Serial.print(i*4095);  
    i += inc;
    Serial.print(" ; ");
    Serial.print(analogRead(pin));
    Serial.print(" ; ");
    Serial.print(i,10);
    Serial.println(" ; ");
    delay(10);
    
}

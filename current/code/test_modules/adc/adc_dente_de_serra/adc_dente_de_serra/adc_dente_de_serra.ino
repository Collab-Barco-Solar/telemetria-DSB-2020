#include <Wire.h>

#define   ADC_12BIT_MAX   4096
#define   BAUD 2000000
#define   pin 4
#define   DAC1 25
#define   dacNormPrecision 0.0039215686274509803921568627451  

int logicLevelADC;
float voltageADC;
double i = 0;

void setup() {
  
  Serial.begin(BAUD);
  pinMode(pin, INPUT);
  /* aguarda a serial estar disponível */
  while (!Serial);
  Serial.println();  
}

void loop() {

    i > 1 ? i = 0 : 1;
    dacWrite( DAC1 , i*255 );
    Serial.print(i*4095);  
    i += dacNormPrecision;
    Serial.print(" ; ");
    Serial.print(analogRead(pin));
    Serial.print(" ; ");
    Serial.print(i,8);
    Serial.println(" ; ");
    delay(10);
    
}

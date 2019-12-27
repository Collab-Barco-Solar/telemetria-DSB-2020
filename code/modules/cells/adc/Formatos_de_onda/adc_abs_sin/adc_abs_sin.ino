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
  
  Serial.print(sin(i*PI)*4095, 5) ;
  dacWrite( DAC1 , sin(i*PI) * 255  );
  Serial.print(" ; ");
  Serial.print(analogRead(pin));
  Serial.println(" ; ");
  i += dacNormPrecision;
  delay(10);
}

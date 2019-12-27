#include <Wire.h>

#define   ADC_12BIT_MAX   4096
#define   BAUD 2000000
#define   pin 4
#define   DAC1 25
#define   dacNormPrecision 0.0039215686274509803921568627451  

int logicLevelADC;
float voltageADC;
uint8_t i = 0;
uint8_t j = 0;
bool alta = false;
void setup() {
  
  Serial.begin(BAUD);
  pinMode(pin, INPUT);
  /* aguarda a serial estar disponível */
  while (!Serial);
  Serial.println();  

}

void loop() {
  
   j > 30 ? alta =(!alta) : 1;
   j > 30 ? j=0 : 1;
   i > 60? i=0 : 1 ;
  if(alta){
    
    dacWrite( DAC1 , 0.5*255 );
    Serial.print(0.5*4095);  
    Serial.print(" ; ");
    Serial.print(analogRead(pin));
    
  }
  else{
    dacWrite( DAC1 , 0*255 );
    Serial.print(0*4095);  
    Serial.print(" ; ");
    Serial.print(analogRead(pin));
    
    
  }
//  Serial.print(" ; ");
//  Serial.print(i);
  Serial.println(" ; ");
  delay(10);
  j++;
  i++;
}

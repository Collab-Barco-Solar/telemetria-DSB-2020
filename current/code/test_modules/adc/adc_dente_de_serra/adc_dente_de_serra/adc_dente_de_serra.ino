#include <Wire.h>

#define   ADC_12BIT_MAX   4096
#define   BAUD 2000000
#define   pin 4
#define   DAC1 25

int logicLevelADC;
float voltageADC;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUD);
  pinMode(pin, INPUT);
  /* aguarda a serial estar disponível */
  while (!Serial);
  Serial.println();  
}
//double passo = 0.00392156863;
double i = 0;
void loop() {

    i > 1 ? i = 0 : 1;
    dacWrite( DAC1 , i*255 );
    Serial.print(i*4095);  
    i += 0.001;
    Serial.print(" ; ");
    Serial.print(analogRead(pin));
    Serial.println(" ; ");
    delay(50);
}

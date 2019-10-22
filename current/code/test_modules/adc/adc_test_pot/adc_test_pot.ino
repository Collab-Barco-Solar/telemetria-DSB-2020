#include <Wire.h>

#define   ADC_12BIT_MAX   4096
#define   BAUD 2000000
#define   pin 4
#define   p5 17.5938359490609
#define   p4  1.21697808640912 
#define   p3  -0.000168313273959029
#define   p2  7.69758075646963e-08
#define   p1  -1.21956845031952e-11 

double valuefitted;
double potvoltage;
double stoptime;
double start;
double value = 0;
float DT5_RATIO = 1.552971576f; // VOLTAGE DIVIDER FOR POTENTIOMETER
void setup() {
  Serial.begin(BAUD);
  pinMode(pin, INPUT);
  /* aguarda a serial estar disponível */
  while (!Serial);
  
}

void loop() {
  start = micros();
  value = analogRead(pin);
  valuefitted = (value*value*value*value*p1)+(value*value*value*p2)+(value*value*p3) + (value*p4) + p5;
  potvoltage = (valuefitted * 3.3)/4095;
  Serial.print(valuefitted);
  Serial.print(" ; ");
  Serial.print(potvoltage * DT5_RATIO * 2);
  Serial.print(" ; ");
  stoptime = micros();
  Serial.print(stoptime-start);
  Serial.println(" ; ");
  delay(50);
}

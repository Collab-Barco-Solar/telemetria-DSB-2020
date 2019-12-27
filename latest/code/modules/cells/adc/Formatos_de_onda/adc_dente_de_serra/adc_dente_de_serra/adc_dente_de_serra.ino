#include <Wire.h>

#define   ADC_12BIT_MAX   4096
#define   BAUD 2000000
#define   pin 4
#define   DAC1 25
#define   p5 17.5938359490609
#define   p4  1.21697808640912 
#define   p3  -0.000168313273959029
#define   p2  7.69758075646963e-08
#define   p1  -1.21956845031952e-11 

int logicLevelADC;
float voltageADC;
double i = 0;
double razao = 16.058823529412;
double value = 0;
double valuefitted;
double stoptime;
double start;
void setup() {
  
  Serial.begin(BAUD);
  pinMode(pin, INPUT);
  /* aguarda a serial estar disponível */
  while (!Serial);
}

void loop() {
    
    i > 255 ? i = 0 : 1;
    
    dacWrite( DAC1 , i );
    Serial.print(i*razao, 4);  
    i += 1;
    Serial.print(" ; ");
    value = analogRead(pin); 
    start = micros();
    valuefitted = (value*value*value*value*p1)+(value*value*value*p2)+(value*value*p3) + (value*p4) + p5;
    stoptime = micros();
    Serial.print(value);
    Serial.print(" ; ");
    Serial.print(valuefitted);
    Serial.print(" ; ");
    // habilitar visualizacao de tempo para execucao do ajuste
    /*
    Serial.print(stoptime-start);
    */
    // habilitar visualização de diferença entre ajuste
    
      Serial.print(" ; ");
      Serial.print(((i*razao)-valuefitted));
   
     // habilitar visualização de diferença sem ajuste
     
      Serial.print(" ; ");
      Serial.print(((i*razao)-value));
     
    Serial.println(" ; ");
    delay(10);
}

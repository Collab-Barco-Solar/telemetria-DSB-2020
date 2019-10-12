#include <Wire.h>
#include <Adafruit_ADS1015.h>
 
/* possibilidades/niveis de acordo com a resolução */
#define   ADC_12BIT_MAX   4096
#define   BAUD 2000000
#define   pin 33
#define   DAC1 25

int logicLevelADC;
double voltageADC;
double inputRangeADC = 3.3;
double voltagePerBitADC = ( inputRangeADC * 2 ) / (ADC_12BIT_MAX - 1) ;
 
 
void setup(void) {
  /* inicializa a serial */
  Serial.begin(BAUD);

  pinMode(pin, INPUT);
  
  /* aguarda a serial estar disponível */
  while (!Serial);
  
  Serial.println();
  Serial.print("ADC volt/bit: ");   Serial.print( voltagePerBitADC * 1000, 4);     Serial.println(" mV/bit");
  Serial.println();
  
  /* imprime a primeira linha com identificacao dos dados */
  Serial.println("ADC RAW \tADC Tensão.");
 
}

double i=0;
 
void loop(void) {
  
  logicLevelADC = analogRead(pin);
  voltageADC = logicLevelADC * voltagePerBitADC;
  
  Serial.print(logicLevelADC);    Serial.print("\t\t");   Serial.print(voltageADC, 8);    Serial.print("\t\t");    Serial.print( sin(i) * 3.3 ) ;    Serial.print("\t\t");   
  Serial.println();  

  i > PI ? i = 0 : 1 ;
  
  dacWrite( DAC1 , sin(i) * 255  );
  
  i += 0.01;
  delay(50);
}

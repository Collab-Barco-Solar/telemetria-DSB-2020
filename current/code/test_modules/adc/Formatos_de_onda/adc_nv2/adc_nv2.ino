#include <Wire.h>
#include <Adafruit_ADS1015.h>
 
/* possibilidades/niveis de acordo com a resolução */
#define   ADC_12BIT_MAX   4096
#define   BAUD 2000000
#define   pin 4
#define   DAC1 25
#define   seletor 14 

int logicLevelADC;
float voltageADC;
double inputRangeADC = 3.3;
float voltagePerBitADC = ( inputRangeADC ) / (ADC_12BIT_MAX - 1) ;
 
 
void setup(void) {
  /* inicializa a serial */
  Serial.begin(BAUD);

  pinMode(pin, INPUT);
  pinMode(seletor, LOW);
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
  Serial.print("Leitura ADC: ");
  Serial.print(logicLevelADC);    Serial.print("\t\t");   
  
  //Serial.print(voltageADC, 8);    Serial.print("\t\t");      
  

  i > 1 ? i = 0 : 1 ;

  if(digitalRead(seletor) == HIGH)
  {
    Serial.print("Escrita DAC: ");
    Serial.print( (sin(i*PI) * 3.3), 8 ) ;    Serial.print("\t\t");
    dacWrite( DAC1 , sin(i*PI) * 255  );
    Serial.print("Erro: "); Serial.print(abs((sin(i*PI) * 3.3) - voltageADC), 8);
    Serial.println();  
  }
  else if(digitalRead(seletor) == LOW)
  {
    Serial.print("Escrita: ");
    Serial.print(4095*0.5, 8);    Serial.print("\t\t");
    //Serial.print(0.5*3.3, 8);    Serial.print("\t\t");
    dacWrite( DAC1 , 1 * 255 );
    //Serial.print("Erro: "); Serial.print(abs(0.5*3.3 - voltageADC), 8);
    Serial.println();  
    
  }
  
  i += 0.01;
  delay(50);
}

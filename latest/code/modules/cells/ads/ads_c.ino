#include <Wire.h>
#include <Adafruit_ADS1015.h>
 
/* possibilidades/niveis de acordo com a resolução */
#define   ADC_16BIT_MAX   65536
#define   BAUD 2000000
 
/* cria instância do conversor analogico digital ADC */
Adafruit_ADS1115 ads(0x48);
 
/*
 * Variaveis
 */
int16_t logicLevelADS;
double voltageADS;
double inputRangeADS = 4.096;
double voltagePerBitADS = ( inputRangeADS * 2) / (ADC_16BIT_MAX - 1) ;
 
 
void setup(void) {
  /* inicializa a serial */
  Serial.begin(BAUD);
 
  /* aguarda a serial estar disponível */
  while (!Serial);
 
  /*
   * configura o ganho do PGA interno do ADS1115
   * - Sem configurar ele inicia automaticamente na escala de +/- 6.144V
   * - lembre-se de não exceder os limites de tensao nas entradas
   * - - VDD+0.3v ou GND-0.3v
   */

  ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
   
//  ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
//  ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
//  ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
//  ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
//  ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
//  ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
 
  /* inicializa o ADC */
  ads.begin();
  
  /*
   * imprime o valor da tensao por bit
   * - ADS1115 (de acordo com o ganho do PGA)
   * - Arduino Nano/Uno com referencia em Vcc
   * - Arduino Nano/Uno com referencia interna de 1.1V
   */
  Serial.println();
  Serial.print("ADS volt/bit: ");   Serial.print( voltagePerBitADS * 1000, 4);     Serial.println(" mV/bit");
  Serial.println();
  
  /* imprime a primeira linha com identificacao dos dados */
  Serial.println("ADS RAW \tADS Tensão.");
 
}
 
void loop(void) {
  
  logicLevelADS = ads.readADC_Differential_0_1();
  voltageADS = logicLevelADS * voltagePerBitADS;
  
  /* imprime os resultados */
  Serial.print(logicLevelADS);    Serial.print("\t\t");   Serial.print(voltageADS, 8);    Serial.print("\t\t");   
  Serial.println();
   
  delay(20);
}

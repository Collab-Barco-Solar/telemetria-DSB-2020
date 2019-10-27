<<<<<<< HEAD:ads/ads.ino
#include <Wire.h>
#include <Adafruit_ADS1015.h>
 
#define   ADC_16BIT_MAX   65536 // Maximum ADC resolution
#define   BAUD 2000000
 
Adafruit_ADS1115 ads(0x48); // ADS object

double ads_bit_Voltage;
 
 
void setup(void) {
  
  Serial.begin(BAUD);

  while (!Serial);

// Choose a gain amount, don't exceed the maximum voltage
  
  ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.0078125mV
 
   
//  ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 0.1875mV (default)
//  ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 0.125mV
//  ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 0.0625mV
//  ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.03125mV
//  ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.015625mV
//  ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.0078125mV
 
  ads.begin();

// Change this variable to the voltage level you selected in the gain

  double ads_InputRange = 0.256;
  ads_bit_Voltage = (ads_InputRange * 2) / (ADC_16BIT_MAX - 1);
 
  Serial.print("ADS volt/bit: ");   Serial.print(ads_bit_Voltage * 1000, 4);     Serial.println(" mV/bit");
  
}
 
void loop(void) {
  // RAW ADC value storage
  int16_t ads_0_1 = ads.readADC_Differential_0_1() *  ads_bit_Voltage;
  
  
  /* imprime os resultados */
  Serial.print(ads_0_1);    Serial.print("\t\t");   Serial.print(ads_0_1 , 8);    Serial.print("\t\t");   
  Serial.println();
   
  delay(20);
}
=======
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
double ads_bit_Voltage;
 
 
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

  ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
 
   
//  ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
//  ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
//  ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
//  ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
//  ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
//  ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
 
  /* inicializa o ADC */
  ads.begin();
 
  /* modifique este valor de acordo com o ganho selecionado */
  double ads_InputRange = 0.256;
 
  /* no range de +-6.144V, 187.502uV/bit */
  ads_bit_Voltage = (ads_InputRange * 2) / (ADC_16BIT_MAX - 1);
 
  /*
   * imprime o valor da tensao por bit
   * - ADS1115 (de acordo com o ganho do PGA)
   * - Arduino Nano/Uno com referencia em Vcc
   * - Arduino Nano/Uno com referencia interna de 1.1V
   */
  Serial.println();
  Serial.print("ADS volt/bit: ");   Serial.print(ads_bit_Voltage * 1000, 4);     Serial.println(" mV/bit");
  Serial.println();
  
  /* imprime a primeira linha com identificacao dos dados */
  Serial.println("ADS RAW \tADS Tensão.");
 
}
 
void loop(void) {
  /* variaveis apra armazenar o valor RAW do adc */
  int16_t ads_ch0 = 0;
  int16_t nano_ch0_0 = 0;           // usando referencia de Vcc (5V)
  int16_t nano_ch0_1 = 0;           // usando referencia interna (1.1V)
  /* variaveis para armazenar o resultado em tensao */
  double ads_Voltage_ch0 = 0.0;
  /* variaveis para armazenar a temperatura */
  
  /********************************************
   * ADS1115 - 16bit ADC
   * - le o ADC
   * - converter o valor RAW em tensao
   * - calcula a temperatura
   ********************************************/
  //ads_ch0 = media(ads) ;
  double ads_0_1 = media(ads) ;
  
  ads_Voltage_ch0 = ads_ch0 * ads_bit_Voltage;
  
  /* imprime os resultados */
  Serial.print(ads_0_1);    Serial.print("\t\t");   Serial.print(ads_Voltage_ch0, 8);    Serial.print("\t\t");   
  Serial.println();
   
  delay(20);
}

double media( Adafruit_ADS1115 adc ) {
  double leituras = 0;

  for (int i = 0 ; i < 100 ; i++ ){
    leituras += adc.readADC_Differential_0_1();
  }

  return leituras/100;
}
>>>>>>> b4d37111899ca47a7019808a62a829e02c2e0c1b:current/code/test_modules/ads/ads.ino

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

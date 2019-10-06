#include <Wire.h>
#include <Adafruit_ADS1015.h>

#define   BAUD 2000000
#define RESISTOR_CONSTANT (98500 + 3831) / 3831

Adafruit_ADS1115 ads(0x48);  /* Use this for the 16-bit version */

int16_t results;

void setup(void)
{
  Serial.begin(BAUD);
   
  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                  ADS1115
  //                                                                  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit =   0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit =   0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit =   0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit =   0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit =   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit =   0.0078125mV

  ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit =   0.125mV
  
  ads.begin();

  Serial.println("Taxa de amostragem: 1s, tensão em mV");
  
}

void loop(void)
{
  
  
  /* Be sure to update this value based on the IC and the gain settings! */
  float   multiplier = 0.125F;  
  //float multiplier = 0.1875F; /* ADS1115  @ +/- 6.144V gain (16-bit results) */

  results = ads.readADC_Differential_0_1();  
    
  //Serial.print("Differential: "); 
  //Serial.print(results); 
  //Serial.print("("); 
  //Serial.print(results); 
  //Serial.print(" "); 
  Serial.println(results * multiplier * RESISTOR_CONSTANT, 10); 
  //Serial.println("mV)");

  delay(1000);
}

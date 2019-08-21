// bibliotecas

#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <Adafruit_ADS1015.h>


//pinos

#define SCK     5     // GPIO5  -- LoRa SX1278's SCK
#define MISO    19    // GPIO19 -- LoRa SX1278's MISnO
#define MOSI    27    // GPIO27 -- LoRa SX1278's MOSI
#define SS      18    // GPIO18 -- LoRa SX1278's CS
#define RST     14    // GPIO14 -- LoRa SX1278's RESET
#define DI0     26    // GPIO26 -- LoRa SX1278's IRQ(Interrupt Request)

#define RXPin    15  // Neo6M RX pin
#define TXPin    12  // Neo6M TX pin
#define GPSBaud 9600 // Neo6M Baud rate


//defines

#define FREQ  915E6   // Operating LoRa frequency
#define SF      7    // Operating LoRa Spread Factor
#define BAND  125E3   // Operating LoRa Bandwidth
#define TXPOWER 20    // Operating LoRa Transmition Power
#define BAUD 2000000  // BAUD serial rate

#define PIN_POTENCIOMETER 36

#define SHUNT    0x48  // Address of the ADC measuring the motor current
#define MODULES  0x49 // Address of the ADC on the solar panel modules
#define BATTERY  0x4A // Address of the ADC on the battery

//objetos

String rssi = "RSSI --";
String packSize = "--";
String packet ;

TinyGPSPlus gps;      // GPS object
HardwareSerial ss(2); // Hardware Serial comunication object

Adafruit_ADS1115 ads_shunt(SHUNT);
Adafruit_ADS1115 ads_modules(MODULES);
Adafruit_ADS1115 ads_battery(BATTERY);




  //   Cheatsheet                                                     ADS1115
  //                                                                  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit =   0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit =   0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit =   0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit =   0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit =   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit =   0.0078125mV


//setup

//functions

double LatitudeGPS( ){

  return gps.location.lat();
}

double LongitudeGPS( ){
  
  return gps.location.lng();
}

char CSV_Separator(){
  return (';');
}

int16_t ShuntRead(){
  ads_shunt.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit =   0.0078125mV
  
  return ads_shunt.readADC_Differential_0_1();
}

int16_t BatteryRead(){
  ads_battery.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit =   0.125mV
  
  return ads_battery.readADC_Differential_0_1();
}

int16_t ModulesRead(){
  ads_modules.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit =   0.125mV
  
  return ads_modules.readADC_Differential_0_1();
}

float PotentiometerRead(){

  return 0;
}

boolean LeftPumpRead(){

  return 0;
}

boolean RightPumpRead(){

  return 0;
}



void setup() {
  
  Serial.begin(BAUD);
  ss.begin(GPSBaud, SERIAL_8N1, TXPin, RXPin); // GPS serial communication

  pinMode(PIN_POTENCIOMETER, INPUT);
  
  while (!Serial);
  Serial.println();
  Serial.println("Boat sender");
  
  SPI.begin(SCK,MISO,MOSI,SS); // LoRa SPI communication
  LoRa.setPins(SS,RST,DI0);
  
  if (!LoRa.begin(FREQ)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  LoRa.setSpreadingFactor(SF);
  LoRa.setSignalBandwidth(BAND);
  LoRa.setTxPower(TXPOWER);
  LoRa.enableCrc();

  
  //LoRa.onReceive(cbk);
  //  LoRa.receive();
  Serial.println("Initialization: ok");
 
  delay(1500);
}

void loop() {
  
  // Create and send packet

  // Update GPS
  gps.encode(ss.read());
  
  LoRa.beginPacket();
  // Write GPS Latitude
  LoRa.print(LatitudeGPS());
  LoRa.print(CSV_Separator());
  // Write GPS Longitude
  LoRa.print(LongitudeGPS());
  LoRa.print(CSV_Separator());
  // Write Shunt reading (motor current)
  LoRa.print(ShuntRead());
  LoRa.print(CSV_Separator());
  // Write Battery voltage (probably using the ADS1115)
  LoRa.print(BatteryRead());
  LoRa.print(CSV_Separator());
  // Write Solar Modules voltage  (probably using the ADS1115)
  LoRa.print(ModulesRead());
  LoRa.print(CSV_Separator());
  // Write the potentiometer state that controls the motor 
  LoRa.print(PotentiometerRead());
  LoRa.print(CSV_Separator());
  // Write left pump state
  LoRa.print(LeftPumpRead());
  LoRa.print(CSV_Separator());
  // Write right pump state
  LoRa.print(RightPumpRead());
  LoRa.print(CSV_Separator());
  

  
  //LoRa.print(counter);
  LoRa.endPacket();

  //delay(50);
}

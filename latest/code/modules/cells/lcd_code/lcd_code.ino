// bibliotecas

#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
//#include <TinyGPS++.h>
//#include <HardwareSerial.h>
//#include <Adafruit_ADS1015.h>
#include <LiquidCrystal_I2C.h>

// set the LCD number of columns and rows
int lcdColumns = 20;
int lcdRows = 4;
char caqui[12] = "OLA CAQUI";
// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

void setup(){
  // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();
}

void loop(){
  // set cursor to first column, first row
  lcd.setCursor(0, 0);
  lcd.print(caqui);

  lcd.setCursor(0,1);
  lcd.print("TALVEZ DE CERTO");
  
}

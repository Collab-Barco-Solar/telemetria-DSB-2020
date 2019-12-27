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
char caqui[12] = "IM:    A";
char algo[4] = "50";
char algo2[4] = "49";
char agricio[17] ="TALVEZ DE CERTO";

char jm[12] = "OLA ICE";
char felipe[17] ="DEU CERTO";
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
  primeiratela(algo);
  delay(2000);
  primeiratela(algo2);
  delay(2000);
  segundatela();
  delay(2000);
}

void primeiratela(char* cao)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(caqui);
  lcd.setCursor(4, 0);
  lcd.print(cao);
  lcd.setCursor(0,1);
  lcd.print(agricio);
}

void segundatela()
{
  lcd.clear();
  lcd.setCursor(0,2);
  lcd.print(jm);
  lcd.setCursor(0,3);
  lcd.print(felipe);
}

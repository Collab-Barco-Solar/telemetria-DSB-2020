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
char feliz[17] ="BOA COMPETICAO!";
char inici[20] = "SOLARES POENTE 2020";
char correnteMotor[9] = "IM: 80A", potMotor[9] = "PM:120W", potGeracao[9] = "PG:400W";
char valorIM[4] = "50", valorPM[4] = "40", valorPG[4] = "39";
char cemLinhaZero[15] = " 0 000 000", cemLinhaUm[15] = "00 0 0 0 0", cemLinhaDois[15] = " 0 0 0 0 0", cemLinhaTres[15] = " 0 000 000";
// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

void setup(){
  // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();
  inicializacao();
  delay(3000);
  telaprincipal();
}

void loop(){
}

void inicializacao()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(feliz);
  lcd.setCursor(0,2);
  lcd.print(inici);
}

void telaprincipal()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(cemLinhaZero);
  lcd.setCursor(0,1);
  lcd.print(cemLinhaUm);
  lcd.setCursor(0,2);
  lcd.print(cemLinhaDois);
  lcd.setCursor(0,3);
  lcd.print(cemLinhaTres);
  lcd.setCursor(12,0);
  lcd.print(correnteMotor);
  lcd.setCursor(12,1);
  lcd.print(potMotor);
  lcd.setCursor(12,2);
  lcd.print(potGeracao);
}

//libraries
#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
//#include <TinyGPS++.h>
//#include <HardwareSerial.h>
//#include <Adafruit_ADS1015.h>
#include <LiquidCrystal_I2C.h>

//set the LCD number of columns and rows
int lcdColumns = 20;
int lcdRows = 4;
char feliz[17] ="BOA COMPETICAO!";
char inici[20] = "SOLARES POENTE 2020";
char correnteMotor[9] = "IM: 80A", potMotor[9] = "PM:120W", potGeracao[9] = "PG:400W";
char valorIM[4] = "50", valorPM[4] = "40", valorPG[4] = "39";
byte chr1[6]={ 
    B1111,
    B1111,
    B1111,
    B1111,
    B1111,
    B1111
};
byte chr2[6] =  { 
    B0000,
    B0000,
    B0000,
    B1111,
    B1111,
    B1111
};
byte chr3[6] =  { 
    B1111,
    B1111,
    B1111,
    B0000,
    B0000,
    B0000
};
//if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

void setup(){
  // initialize LCD
  Serial.begin(115200);
  Serial.println("deu certo");
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();
  lcd.createChar(0, chr1);
  lcd.createChar(1, chr2);
  lcd.createChar(2, chr3);
  inicializacao();
  //delay(3000);
  //num0();
 // telaprincipal();
}

void loop()
{  
}

void inicializacao()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(feliz);
  lcd.setCursor(0,2);
  lcd.print(inici);
}

void num0()
{
  lcd.setCursor(0,0);
  lcd.write(0);
  lcd.setCursor(0,1);
  lcd.write(0);
  lcd.setCursor(0,2);
  lcd.write(0);
  lcd.setCursor(0,3);
  lcd.write(0);
  lcd.setCursor(1,0);
  lcd.write(0);
  lcd.setCursor(1,3);
  lcd.write(0);
  lcd.setCursor(2,0);
  lcd.write(0);
  lcd.setCursor(2,1);
  lcd.write(0);
  lcd.setCursor(2,2);
  lcd.write(0);
  lcd.setCursor(2,3);
  lcd.write(0);
// lcd.setCursor(0,0);
// for(int i=0;i<3;i++)
// {
// lcd.write(0);
// lcd.setCursor(i,0);
// }
// lcd.setCursor(0,1);
// lcd.write(0);
// lcd.print(" ");
// lcd.write(0);
// lcd.setCursor(0,2);
// lcd.write(0);
// lcd.print(" ");
// lcd.write(0);
// lcd.setCursor(0,3);
// for(int i=0;i<3;i++)
// lcd.write(0);
}

void telaprincipal()
{
  lcd.clear();
  lcd.setCursor(0,0);
  
//  lcd.setCursor(0,1);
//  lcd.print(cemLinhaUm);
//  lcd.setCursor(0,2);
//  lcd.print(cemLinhaDois);
//  lcd.setCursor(0,3);
//  lcd.print(cemLinhaTres);
//  lcd.setCursor(12,0);
//  lcd.print(correnteMotor);
//  lcd.setCursor(12,1);
//  lcd.print(potMotor);
//  lcd.setCursor(12,2);
//  lcd.print(potGeracao);
}

void num1()
{
 lcd.setCursor(0,0);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
 lcd.setCursor(0,1);
 lcd.write(0);
 lcd.print(" ");
 lcd.write(0);
 lcd.setCursor(0,2);
 lcd.write(0);
 lcd.print(" ");
 lcd.write(0);
 lcd.setCursor(0,3);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
}

void num2()
{
 lcd.setCursor(0,0);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
 lcd.setCursor(0,1);
 lcd.write(0);
 lcd.print(" ");
 lcd.write(0);
 lcd.setCursor(0,2);
 lcd.write(0);
 lcd.print(" ");
 lcd.write(0);
 lcd.setCursor(0,3);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
}

void num3()
{
 lcd.setCursor(0,0);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
 lcd.setCursor(0,1);
 lcd.write(0);
 lcd.print(" ");
 lcd.write(0);
 lcd.setCursor(0,2);
 lcd.write(0);
 lcd.print(" ");
 lcd.write(0);
 lcd.setCursor(0,3);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
}

void num4()
{
 lcd.setCursor(0,0);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
 lcd.setCursor(0,1);
 lcd.write(0);
 lcd.print(" ");
 lcd.write(0);
 lcd.setCursor(0,2);
 lcd.write(0);
 lcd.print(" ");
 lcd.write(0);
 lcd.setCursor(0,3);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
}

void num5()
{
 lcd.setCursor(0,0);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
 lcd.setCursor(0,1);
 lcd.write(0);
 lcd.print(" ");
 lcd.write(0);
 lcd.setCursor(0,2);
 lcd.write(0);
 lcd.print(" ");
 lcd.write(0);
 lcd.setCursor(0,3);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
}

void num6()
{
 lcd.setCursor(0,0);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
 lcd.setCursor(0,1);
 lcd.write(0);
 lcd.print(" ");
 lcd.write(0);
 lcd.setCursor(0,2);
 lcd.write(0);
 lcd.print(" ");
 lcd.write(0);
 lcd.setCursor(0,3);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
}

void num7()
{
 lcd.setCursor(0,0);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
 lcd.setCursor(0,1);
 lcd.write(0);
 lcd.print(" ");
 lcd.write(0);
 lcd.setCursor(0,2);
 lcd.write(0);
 lcd.print(" ");
 lcd.write(0);
 lcd.setCursor(0,3);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
}

void num8()
{
 lcd.setCursor(0,0);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
 lcd.setCursor(0,1);
 lcd.write(0);
 lcd.print(" ");
 lcd.write(0);
 lcd.setCursor(0,2);
 lcd.write(0);
 lcd.print(" ");
 lcd.write(0);
 lcd.setCursor(0,3);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
}

void num9()
{
 lcd.setCursor(0,0);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
 lcd.setCursor(0,1);
 lcd.write(0);
 lcd.print(" ");
 lcd.write(0);
 lcd.setCursor(0,2);
 lcd.write(0);
 lcd.print(" ");
 lcd.write(0);
 lcd.setCursor(0,3);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
}

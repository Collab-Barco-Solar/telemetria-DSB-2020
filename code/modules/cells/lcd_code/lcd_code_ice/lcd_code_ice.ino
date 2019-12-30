#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
//#include <TinyGPS++.h>
//#include <HardwareSerial.h>
//#include <Adafruit_ADS1015.h>
#include <LiquidCrystal_I2C.h>

int lcdColumns = 20;
int lcdRows = 4;
char feliz[17] ="BOA COMPETICAO!";
char inici[20] = "SOLARES POENTE 2020";
char correnteMotor[9] = "IM: 80A", potMotor[9] = "PM:120W", potGeracao[9] = "PG:400W";
char valorIM[4] = "50", valorPM[4] = "40", valorPG[4] = "39";
byte chr0[8]={ 
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111
};
byte chr1[8] =  { 
    B00000,
    B00000,
    B00000,
    B00000,
    B11111,
    B11111,
    B11111,
    B11111
};
byte chr2[8] =  { 
    B11111,
    B11111,
    B11111,
    B11111,
    B00000,
    B00000,
    B00000,
    B00000
};
//if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

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
  lcd.setCursor(12,0);
  lcd.print(correnteMotor);
  lcd.setCursor(12,1);
  lcd.print(potMotor);
  lcd.setCursor(12,2);
  lcd.print(potGeracao);
}

void num0(int i)
{
  lcd.setCursor(i,0);
  lcd.write(0);
  lcd.setCursor(i+1,0);
  lcd.write(0);
  lcd.setCursor(i+2,0);
  lcd.write(0);
  lcd.setCursor(i,1);
  lcd.write(0);
  lcd.setCursor(i+2,1);
  lcd.write(0);
  lcd.setCursor(i,2);
  lcd.write(0);
  lcd.setCursor(i+2,2);
  lcd.write(0);
  lcd.setCursor(i,3);
  lcd.write(0);
  lcd.setCursor(i+1,3);
  lcd.write(0);
  lcd.setCursor(i+2,3);
  lcd.write(0);
}

void num1(int i)
{
  lcd.setCursor(i+1,0);
  lcd.write(0);
  lcd.setCursor(i,1);
  lcd.write(0);
  lcd.setCursor(i+1,1);
  lcd.write(0);
  lcd.setCursor(i+1,2);
  lcd.write(0);
  lcd.setCursor(i+1,3);
  lcd.write(0);
}

void num2(int i)
{
  lcd.setCursor(i,0);
  lcd.write(0);
  lcd.setCursor(i+1,0);
  lcd.write(0);
  lcd.setCursor(i+2,0);
  lcd.write(0);
  lcd.setCursor(i,1);
  lcd.write(1);
  lcd.setCursor(i+1,1);
  lcd.write(1);
  lcd.setCursor(i+2,1);
  lcd.write(0);
  lcd.setCursor(i,2);
  lcd.write(0);
  lcd.setCursor(i+1,2);
  lcd.write(2);
  lcd.setCursor(i+2,2);
  lcd.write(2);
  lcd.setCursor(i,3);
  lcd.write(0);
  lcd.setCursor(i+1,3);
  lcd.write(0);
  lcd.setCursor(i+2,3);
  lcd.write(0);
}

void num3(int i)
{
  lcd.setCursor(i,0);
  lcd.write(0);
  lcd.setCursor(i+1,0);
  lcd.write(0);
  lcd.setCursor(i+2,0);
  lcd.write(0);
  lcd.setCursor(i,1);
  lcd.write(1);
  lcd.setCursor(i+1,1);
  lcd.write(1);
  lcd.setCursor(i+2,1);
  lcd.write(0);
  lcd.setCursor(i,2);
  lcd.write(2);
  lcd.setCursor(i+1,2);
  lcd.write(2);
  lcd.setCursor(i+2,2);
  lcd.write(0);
  lcd.setCursor(i,3);
  lcd.write(0);
  lcd.setCursor(i+1,3);
  lcd.write(0);
  lcd.setCursor(i+2,3);
  lcd.write(0);
}

void num4(int i)
{
  lcd.setCursor(i,0);
  lcd.write(0);
  lcd.setCursor(i+2,0);
  lcd.write(0);
  lcd.setCursor(i,1);
  lcd.write(0);
  lcd.setCursor(i+1,1);
  lcd.write(1);
  lcd.setCursor(i+2,1);
  lcd.write(0);
  lcd.setCursor(i,2);
  lcd.write(2);
  lcd.setCursor(i+1,2);
  lcd.write(2);
  lcd.setCursor(i+2,2);
  lcd.write(0);
  lcd.setCursor(i+2,3);
  lcd.write(0);
}

void num5(int i)
{
  lcd.setCursor(i,0);
  lcd.write(0);
  lcd.setCursor(i+1,0);
  lcd.write(0);
  lcd.setCursor(i+2,0);
  lcd.write(0);
  lcd.setCursor(i,1);
  lcd.write(0);
  lcd.setCursor(i+1,1);
  lcd.write(1);
  lcd.setCursor(i+2,1);
  lcd.write(1);
  lcd.setCursor(i,2);
  lcd.write(2);
  lcd.setCursor(i+1,2);
  lcd.write(2);
  lcd.setCursor(i+2,2);
  lcd.write(0);
  lcd.setCursor(i,3);
  lcd.write(0);
  lcd.setCursor(i+1,3);
  lcd.write(0);
  lcd.setCursor(i+2,3);
  lcd.write(0);
}

void num6(int i)
{
  lcd.setCursor(i,0);
  lcd.write(0);
  lcd.setCursor(i+1,0);
  lcd.write(0);
  lcd.setCursor(i+2,0);
  lcd.write(0);
  lcd.setCursor(i,1);
  lcd.write(0);
  lcd.setCursor(i+1,1);
  lcd.write(1);
  lcd.setCursor(i+2,1);
  lcd.write(1);
  lcd.setCursor(i,2);
  lcd.write(0);
  lcd.setCursor(i+1,2);
  lcd.write(2);
  lcd.setCursor(i+2,2);
  lcd.write(0);
  lcd.setCursor(i,3);
  lcd.write(0);
  lcd.setCursor(i+1,3);
  lcd.write(0);
  lcd.setCursor(i+2,3);
  lcd.write(0);
}

void num7(int i)
{
  lcd.setCursor(i,0);
  lcd.write(0);
  lcd.setCursor(i+1,0);
  lcd.write(0);
  lcd.setCursor(i+2,0);
  lcd.write(0);
  lcd.setCursor(i+0,1);
  lcd.write(0);
  lcd.setCursor(i+2,1);
  lcd.write(0);
  lcd.setCursor(i+2,2);
  lcd.write(0);
  lcd.setCursor(i+2,3);
  lcd.write(0);
}

void num8(int i)
{
  lcd.setCursor(i,0);
  lcd.write(0);
  lcd.setCursor(i+1,0);
  lcd.write(0);
  lcd.setCursor(i+2,0);
  lcd.write(0);
  lcd.setCursor(i,1);
  lcd.write(0);
  lcd.setCursor(i+1,1);
  lcd.write(1);
  lcd.setCursor(i+2,1);
  lcd.write(0);
  lcd.setCursor(i,2);
  lcd.write(0);
  lcd.setCursor(i+1,2);
  lcd.write(2);
  lcd.setCursor(i+2,2);
  lcd.write(0);
  lcd.setCursor(i,3);
  lcd.write(0);
  lcd.setCursor(i+1,3);
  lcd.write(0);
  lcd.setCursor(i+2,3);
  lcd.write(0);
}

void num9(int i)
{
  lcd.setCursor(i,0);
  lcd.write(0);
  lcd.setCursor(i+1,0);
  lcd.write(0);
  lcd.setCursor(i+2,0);
  lcd.write(0);
  lcd.setCursor(i,1);
  lcd.write(0);
  lcd.setCursor(i+1,1);
  lcd.write(1);
  lcd.setCursor(i+2,1);
  lcd.write(0);
  lcd.setCursor(i,2);
  lcd.write(2);
  lcd.setCursor(i+1,2);
  lcd.write(2);
  lcd.setCursor(i+2,2);
  lcd.write(0);
  lcd.setCursor(i+2,3);
  lcd.write(0);
}

void setup(){
  int j=0;
  int k=3;
  int l=7;
  Serial.begin(115200);
  Serial.println("deu certo");
  // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();
  lcd.createChar(0, chr0);
  lcd.createChar(1, chr1);
  lcd.createChar(2, chr2);
  inicializacao();
  delay(2000);
  lcd.clear();
  num1(j);
  delay(100);
  num0(k);
  delay(100);
  num0(l);
  delay(100);
  telaprincipal();
}

void loop()
{
  
}

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define BAUD 9600
#define LCD_ADDRESS 0x27
#define ANALOGPIN A0
#define CONVERSION 2

//seta o i2c do lcd
LiquidCrystal_I2C lcd(LCD_ADDRESS,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line displaye
  

void setup(){
  //seta o serial do nano
  Serial.begin(BAUD);
  lcd.init();
  lcd.backlight();
  //seta o pino de leitura analogica
  pinMode(ANALOGPIN, INPUT);
  
}

void loop(){

  // fazer leitura analogica
  double batteryVoltageBits = analogRead(A0);
  // multiplicar por fator linear
  double batteryVoltage = batteryVoltageBits * CONVERSION;
  // printar valor na tela
  lcd.write(batteryVoltage);
  delay(1000);
  lcd.clear();
  
}

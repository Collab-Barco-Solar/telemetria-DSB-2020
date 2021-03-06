 // bibliotecas

#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <Adafruit_ADS1015.h>
#include <LiquidCrystal_I2C.h>


//LoRa transmission and GPS pins

#define SCK     5     // GPIO5  -- LoRa SX1278's SCK
#define MISO    19    // GPIO19 -- LoRa SX1278's MISnO
#define MOSI    27    // GPIO27 -- LoRa SX1278's MOSI
#define SS      18    // GPIO18 -- LoRa SX1278's CS
#define RST     14    // GPIO14 -- LoRa SX1278's RESET
#define DI0     26    // GPIO26 -- LoRa SX1278's IRQ(Interrupt Request)

#define RXPin    15  // Neo6M RX pin
#define TXPin    12  // Neo6M TX pin
#define GPSBaud 9600 // Neo6M Baud rate

// Mux defines

#define S0 32 //MUX control pins
#define S1 14
#define S2 13
#define S3 0
#define MUX_SIG 4 //MUX input Pin

// ACS712 defines
const int mVperAmp = 66;
const int acsVoltageOffSet = 2500; // milivolts voltage acsVoltageOffSet
const int acsVoltageInput = 5000; // milivolts voltage

// polynomial coefficients (ADC Adjustment)

const float p5 = 17.5938359490609;
const float p4 = 1.21697808640912;
const float p3 = -0.000168313273959029;
const float p2 =  7.69758075646963e-08;
const float p1 = -1.21956845031952e-11;

char buf[20];
// MUX input pins

int DMSMux = 1;
int ReverseMux = 3;
int OnOffMux = 4;
int CruiseMux = 5;
int PotMux = 6;
int CBMux = 8;
int BBMux = 7;
int BEMux = 0;
int CEMux = 9;
int BatAMux = 10;
int BatBankMux = 11;
int PhotoMux = 12;
int ACS1Mux = 14;
int ACS2Mux = 13;

// Other Variables
float current;

// Not multiplexed pins
#define PIN_BAT_AUX 13
#define PIN_POTENCIOMETER 14
#define PIN_BAT_BANK_V 2
#define PIN_BAT_BANK_C 21
#define PIN_MOTOR 22


// Other defines

#define FREQ  915E6   // Operating LoRa frequency
#define SF      7     // Operating LoRa Spread Factor
#define BAND  125E3   // Operating LoRa Bandwidth
#define TXPOWER 20    // Operating LoRa Transmition Power
#define CODINGRATE 8  // LoRa Coding Rate (between 4 and 8)
#define SYNCWORD 0x2D // LoRa Sync Word (default is 0x12)
#define BAUD 2000000  // BAUD serial rate


#define ADS    0x48  // Address of the ADC measuring the motor and PV modules current

// Conversion Ratios (Voltage Divider)

const float DT1_RATIO = 19.333333333f; // atualizar com valores medidos dos resistores
const float DT2_RATIO = 4.970588235f; // atualizar com valores medidos dos resistores
const float DT3_RATIO = 28.5f; // atualizar com valores medidos dos resistores
const float DT4_RATIO = 1.564102564f; // atualizar com valores medidos de resistores
const float DT5_RATIO = 1.552971576f; // VOLTAGE DIVIDER FOR POTENTIOMETER

// Objects

String rssi = "RSSI --";
String packSize = "--";
String packet;

TinyGPSPlus gps;      // GPS object
HardwareSerial ss(2); // Hardware Serial comunication object

Adafruit_ADS1115 ads(ADS);

//   Cheatsheet                                                     ADS1115
//                                                                  -------
// ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit =   0.1875mV (default)
// ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit =   0.125mV
// ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit =   0.0625mV
// ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit =   0.03125mV
// ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit =   0.015625mV
// ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit =   0.0078125mV

// Variables
double boat_speed;

// functions

// Coisas do LCD
float screenDuration;
//ActualScreen = 0 (tela principal - Velocidade grande e powers)
//ActualScreen = 1 (Tela Potenciometro)
//ActualScreen = 2 (Low Battery screen)
//    ||       = 3 (Low Efficiency status)
byte ActualScreen;
bool temporaryScreen;
// necessario para caracteres grandes no LCD
// CHARS
byte chr0[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
byte chr1[8] = {
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
LiquidCrystal_I2C lcd(0x27, 20, 4);
// Cria numeros grandes
void num0(int i)
{
  lcd.setCursor(i, 0);
  lcd.write(0);
  lcd.setCursor(i + 1, 0);
  lcd.write(0);
  lcd.setCursor(i + 2, 0);
  lcd.write(0);
  lcd.setCursor(i, 1);
  lcd.write(0);
  lcd.setCursor(i + 2, 1);
  lcd.write(0);
  lcd.setCursor(i, 2);
  lcd.write(0);
  lcd.setCursor(i + 2, 2);
  lcd.write(0);
  lcd.setCursor(i, 3);
  lcd.write(0);
  lcd.setCursor(i + 1, 3);
  lcd.write(0);
  lcd.setCursor(i + 2, 3);
  lcd.write(0);
}

void num1(int i)
{
  lcd.setCursor(i + 1, 0);
  lcd.write(0);
  lcd.setCursor(i, 1);
  lcd.write(0);
  lcd.setCursor(i + 1, 1);
  lcd.write(0);
  lcd.setCursor(i + 1, 2);
  lcd.write(0);
  lcd.setCursor(i + 1, 3);
  lcd.write(0);
}

void num2(int i)
{
  lcd.setCursor(i, 0);
  lcd.write(0);
  lcd.setCursor(i + 1, 0);
  lcd.write(0);
  lcd.setCursor(i + 2, 0);
  lcd.write(0);
  lcd.setCursor(i, 1);
  lcd.write(1);
  lcd.setCursor(i + 1, 1);
  lcd.write(1);
  lcd.setCursor(i + 2, 1);
  lcd.write(0);
  lcd.setCursor(i, 2);
  lcd.write(0);
  lcd.setCursor(i + 1, 2);
  lcd.write(2);
  lcd.setCursor(i + 2, 2);
  lcd.write(2);
  lcd.setCursor(i, 3);
  lcd.write(0);
  lcd.setCursor(i + 1, 3);
  lcd.write(0);
  lcd.setCursor(i + 2, 3);
  lcd.write(0);
}

void num3(int i)
{
  lcd.setCursor(i, 0);
  lcd.write(0);
  lcd.setCursor(i + 1, 0);
  lcd.write(0);
  lcd.setCursor(i + 2, 0);
  lcd.write(0);
  lcd.setCursor(i, 1);
  lcd.write(1);
  lcd.setCursor(i + 1, 1);
  lcd.write(1);
  lcd.setCursor(i + 2, 1);
  lcd.write(0);
  lcd.setCursor(i, 2);
  lcd.write(2);
  lcd.setCursor(i + 1, 2);
  lcd.write(2);
  lcd.setCursor(i + 2, 2);
  lcd.write(0);
  lcd.setCursor(i, 3);
  lcd.write(0);
  lcd.setCursor(i + 1, 3);
  lcd.write(0);
  lcd.setCursor(i + 2, 3);
  lcd.write(0);
}

void num4(int i)
{
  lcd.setCursor(i, 0);
  lcd.write(0);
  lcd.setCursor(i + 2, 0);
  lcd.write(0);
  lcd.setCursor(i, 1);
  lcd.write(0);
  lcd.setCursor(i + 1, 1);
  lcd.write(1);
  lcd.setCursor(i + 2, 1);
  lcd.write(0);
  lcd.setCursor(i, 2);
  lcd.write(2);
  lcd.setCursor(i + 1, 2);
  lcd.write(2);
  lcd.setCursor(i + 2, 2);
  lcd.write(0);
  lcd.setCursor(i + 2, 3);
  lcd.write(0);
}

void num5(int i)
{
  lcd.setCursor(i, 0);
  lcd.write(0);
  lcd.setCursor(i + 1, 0);
  lcd.write(0);
  lcd.setCursor(i + 2, 0);
  lcd.write(0);
  lcd.setCursor(i, 1);
  lcd.write(0);
  lcd.setCursor(i + 1, 1);
  lcd.write(1);
  lcd.setCursor(i + 2, 1);
  lcd.write(1);
  lcd.setCursor(i, 2);
  lcd.write(2);
  lcd.setCursor(i + 1, 2);
  lcd.write(2);
  lcd.setCursor(i + 2, 2);
  lcd.write(0);
  lcd.setCursor(i, 3);
  lcd.write(0);
  lcd.setCursor(i + 1, 3);
  lcd.write(0);
  lcd.setCursor(i + 2, 3);
  lcd.write(0);
}

void num6(int i)
{
  lcd.setCursor(i, 0);
  lcd.write(0);
  lcd.setCursor(i + 1, 0);
  lcd.write(0);
  lcd.setCursor(i + 2, 0);
  lcd.write(0);
  lcd.setCursor(i, 1);
  lcd.write(0);
  lcd.setCursor(i + 1, 1);
  lcd.write(1);
  lcd.setCursor(i + 2, 1);
  lcd.write(1);
  lcd.setCursor(i, 2);
  lcd.write(0);
  lcd.setCursor(i + 1, 2);
  lcd.write(2);
  lcd.setCursor(i + 2, 2);
  lcd.write(0);
  lcd.setCursor(i, 3);
  lcd.write(0);
  lcd.setCursor(i + 1, 3);
  lcd.write(0);
  lcd.setCursor(i + 2, 3);
  lcd.write(0);
}

void num7(int i)
{
  lcd.setCursor(i, 0);
  lcd.write(0);
  lcd.setCursor(i + 1, 0);
  lcd.write(0);
  lcd.setCursor(i + 2, 0);
  lcd.write(0);
  lcd.setCursor(i + 0, 1);
  lcd.write(0);
  lcd.setCursor(i + 2, 1);
  lcd.write(0);
  lcd.setCursor(i + 2, 2);
  lcd.write(0);
  lcd.setCursor(i + 2, 3);
  lcd.write(0);
}

void num8(int i)
{
  lcd.setCursor(i, 0);
  lcd.write(0);
  lcd.setCursor(i + 1, 0);
  lcd.write(0);
  lcd.setCursor(i + 2, 0);
  lcd.write(0);
  lcd.setCursor(i, 1);
  lcd.write(0);
  lcd.setCursor(i + 1, 1);
  lcd.write(1);
  lcd.setCursor(i + 2, 1);
  lcd.write(0);
  lcd.setCursor(i, 2);
  lcd.write(0);
  lcd.setCursor(i + 1, 2);
  lcd.write(2);
  lcd.setCursor(i + 2, 2);
  lcd.write(0);
  lcd.setCursor(i, 3);
  lcd.write(0);
  lcd.setCursor(i + 1, 3);
  lcd.write(0);
  lcd.setCursor(i + 2, 3);
  lcd.write(0);
}


void num9(int i)
{
  lcd.setCursor(i, 0);
  lcd.write(0);
  lcd.setCursor(i + 1, 0);
  lcd.write(0);
  lcd.setCursor(i + 2, 0);
  lcd.write(0);
  lcd.setCursor(i, 1);
  lcd.write(0);
  lcd.setCursor(i + 1, 1);
  lcd.write(1);
  lcd.setCursor(i + 2, 1);
  lcd.write(0);
  lcd.setCursor(i, 2);
  lcd.write(2);
  lcd.setCursor(i + 1, 2);
  lcd.write(2);
  lcd.setCursor(i + 2, 2);
  lcd.write(0);
  lcd.setCursor(i + 2, 3);
  lcd.write(0);
}

// TELAS LCD
void mainScreen(float velocity, float powMotor, float powBatOut, float powPV, int batStatus)
{

}
void potScreen(float potValue)
{

}
void lowBatScreen(float velocity, float powMotor, float powBatOut, float powPV, int batStatus)
{

}
// implementando lcd para teste:
void potentiomenterScreen(char* buffer)
{
  lcd.setCursor(0, 0);
  lcd.print("POT: ");
  lcd.setCursor(5, 0);
  lcd.print(buffer);
  lcd.setCursor(0, 3);
  lcd.print("SOLARES-POENTE 2019");
}
/*void screenTimer(float screenStartTimer)
  {
    float screenEndTimer = milis();
    if(screenDuration >= (screenEndTimer-screenStartTimer))
    {
      temporaryScreen = false;
    }
  }

  void potHistoryManager(float potActual)
  {
    if(potBufferCounter < length(potHistory))
    {
      potHistory[potBufferCounter] = potActual;
    }
    else
    {
      potBufferCounter = 1;
      potHistory[potBufferCounter] = potActual;
      PotCircled = true;
    }
    sumPots = 0;
    for(runner = 1; runner < ((PotCircled == true)?length(potHistory):potBufferCounter)
    {
      sumPots = sumPots +  potHistory[runner];
    }
    //implementar biblioteca agricio com delay apropriado para exibição de Telas
    // criar variável average
    // Parece necessário realizar a operação de divisão, apenas enquanto potCircled por false.
  }
*/
//Multiplexed Measures
float polyfit(float value)
{
  float fittedReading;
  fittedReading = (value * value * value * value * p1) + (value * value * value * p2) + (value * value * p3) + (value * p4) + p5;

  return fittedReading;
}
void SetMuxChannel ( int channel ) {
  digitalWrite(S0, channel >> 0 & 1);
  digitalWrite(S1, channel >> 1 & 1);
  digitalWrite(S2, channel >> 2 & 1);
  digitalWrite(S3, channel >> 3 & 1);
  delay(10);
}
// Getting GPS latitude
double LatitudeGPS( ) {
  return gps.location.lat();
}
// Getting GPS longitude
double LongitudeGPS( ) {
  return gps.location.lng();
}
char CSV_Separator() {
  return (';');
}
float MotorCurrentRead() {
  ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit =   0.0078125mV

  return ads.readADC_Differential_0_1();
}
float BatteryCurrentRead() { // battery bank read
  ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit =   0.125mV
  return ads.readADC_Differential_2_3();
}
float PotentiometerRead() {
  SetMuxChannel(PotMux);
  float readVoltage = (polyfit(analogRead(MUX_SIG)) * 3.3) / 4095; //if analog read == 4095, it is reading 3.3V, so convert the reading from bits to Voltage
  //potHistoryManager(readVoltage);
  sprintf(buf, "%.1f", (readVoltage * DT5_RATIO * 2));
  potentiomenterScreen(buf);
  return readVoltage * DT5_RATIO * 2; //Multiply by the ratio of the voltage divider to find the true voltage value
}
float acsCurrentConversion(float Vacs)
{
  float MeasuredCurrent;
  MeasuredCurrent = ((Vacs - acsVoltageOffSet) / mVperAmp);
  return MeasuredCurrent;
}
boolean DmsRead() {
  SetMuxChannel(DMSMux);;
  return (!(analogRead(MUX_SIG) < 300)); //If it's less than 300 bits, then consider the button as closed and dms on
}

boolean ButtonReverseRead(){
SetMuxChannel(ReverseMux);

return (!(analogRead(MUX_SIG) < 300)); //If it's less than 300 bits, then consider the button as closed
}

boolean ButtonMotorRead() { //On Off button
  SetMuxChannel(OnOffMux);

  return (!(analogRead(MUX_SIG) < 300)); //If it's less than 300 bits, then consider the button as closed
}
/*
  boolean ButtonCruiseRead(){
  SetMuxChannel(CruiseMux);
  return (!(analogRead(MUX_SIG) < 300)); //If it's less than 300 bits, then consider the button as closed
  }
*/
/*
  float CoolerLeftRead(){
   SetMuxChannel(CBMux);
   float readVoltage = (analogRead(MUX_SIG) * 3.3) / 4095;  //if analog read == 4095, it is reading 3.3V, so convert the reading from bits to Voltage

   return readVoltage * DT2_RATIO; //Multiply by the ratio of the voltage divider to find the true voltage value
  }
  float CoolerRightRead(){
   SetMuxChannel(CEMux);
   float readVoltage = (analogRead(MUX_SIG) * 3.3) / 4095;  //if analog read == 4095, it is reading 3.3V, so convert the reading from bits to Voltage

   return readVoltage * DT2_RATIO; //Multiply by the ratio of the voltage divider to find the true voltage value
  }
*/
float AuxiliaryBatteryRead() {
  SetMuxChannel(BatAMux);
  float readVoltage = (polyfit(analogRead(MUX_SIG)) * 3.3) / 4095;  //if analog read == 4095, it is reading 3.3V, so convert the reading from bits to Voltage

  return readVoltage * DT2_RATIO; //Multiply by the ratio of the voltage divider to find the true voltage value
}
float AuxiliaryBatteryCurrentRead() {
  SetMuxChannel(ACS1Mux);
  float readVoltage = (polyfit(analogRead(MUX_SIG)) * 3.3) / 4095;  //if analog read == 4095, it is reading 3.3V, so convert the reading from bits to Voltage
  current = acsCurrentConversion(readVoltage * DT4_RATIO);
  return current; //Multiply by the ratio of the voltage divider to find the true voltage value
}
float PhotovoltaicModulesRead() {
  SetMuxChannel(PhotoMux);
  float readVoltage = (polyfit(analogRead(MUX_SIG)) * 3.3) / 4095;  //if analog read == 4095, it is reading 3.3V, so convert the reading from bits to Voltage

  return readVoltage * DT3_RATIO; //Multiply by the ratio of the voltage divider to find the true voltage value
}
float BatteryBankRead() {
  SetMuxChannel(BatBankMux);
  float readVoltage = (polyfit(analogRead(MUX_SIG)) * 3.3) / 4095;  //if analog read == 4095, it is reading 3.3V, so convert the reading from bits to Voltage

  return readVoltage * DT1_RATIO; //Multiply by the ratio of the voltage divider to find the true voltage value
}
boolean LeftPumpRead() {
  SetMuxChannel(BBMux);

  return (!(analogRead(MUX_SIG) < 300)); //If it's less than 300 bits, then consider the button as closed
}
boolean RightPumpRead() {
  SetMuxChannel(BEMux);

  return (!(analogRead(MUX_SIG) < 300)); //If it's less than 300 bits, then consider the button as closed
}
/*Battery status screen - Begin
  int DisplayBatteryStatus(){ //dispor a porcentagem da bateria no lcd
  int a, b, c, status=BatteryVoltageRead()/(48)*100; //trocar o nome da função, que, na verdade, já existe
  //aproximar o valor (?) - CONFERIR!
  // interessante criar funcao que faca a separacao de algarismos
  a=status/100;
  if(a==1)
  {
    num1(0);
    num0(3);
    num0(7);
  }
  else{
    a=0;
    b=status/10;
    c=status%10;
    switch (b){
      case 1:
        num1(4);
        break;
      case 2:
        num2(3);
      case 3:
        num3(3);
      case 4:
        num4(3);
      case 5:
        num5(3);
      case 6:
        num6(3);
      case 7:
        num7(3);
      case 8:
        num8(3);
      case 9:
        num9(3);
    }
    switch (c){
      case 0:
        num0(7);
        break;
      case 1:
        num1(8);
        break;
      case 2:
        num2(7);
      case 3:
        num3(7);
      case 4:
        num4(7);
      case 5:
        num5(7);
      case 6:
        num6(7);
      case 7:
        num7(7);
      case 8:
        num8(7);
      case 9:
        num9(7);
    }
  }
  }
*/

//setup
void setup() {
  // lcd thigs
  // initialize LCD
  lcd.init();
  // turn on LCD backlight
  lcd.backlight();
  //Cria blocos de chars
  lcd.createChar(0, chr0);
  lcd.createChar(1, chr1);
  lcd.createChar(2, chr2);
  //  float potHistory[20];
  //  int potBufferCounter = 1;
  //  bool PotCircled = false;
  Serial.begin(BAUD);
  ss.begin(GPSBaud, SERIAL_8N1, TXPin, RXPin); // GPS serial communication

  //pinMode(PIN_POTENCIOMETER, INPUT);
  //MUX pins
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(MUX_SIG, INPUT);
  digitalWrite(S0, LOW);
  digitalWrite(S1, LOW);
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);

  while (!Serial);
  Serial.println();
  Serial.println("Boat sender");

  SPI.begin(SCK, MISO, MOSI, SS); // LoRa SPI communication
  LoRa.setPins(SS, RST, DI0);

  if (!LoRa.begin(FREQ)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setSpreadingFactor(SF);
  LoRa.setSignalBandwidth(BAND);
  LoRa.setTxPower(TXPOWER);
  LoRa.enableCrc();
  LoRa.setCodingRate4(CODINGRATE);
  LoRa.setSyncWord(SYNCWORD);

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
  // Write GPS speed
  boat_speed = gps.speed.knots();
  LoRa.print(boat_speed);
  LoRa.print(CSV_Separator());

  //Measures

  //Write DMS reading
  LoRa.print(DmsRead());
  LoRa.print(CSV_Separator());
  
  //Write reverse button
  LoRa.print(ButtonReverseRead()); //For all the buttons -> "true" means closed and "false" means open
  LoRa.print(CSV_Separator());
  
  //Write motor button state (on/off)
  LoRa.print(ButtonMotorRead()); //For all the buttons -> "true" means closed and "false" means open
  LoRa.print(CSV_Separator());
  /*
    //Write cruise button state
    LoRa.print(ButtonCruiseRead()); //For all the buttons -> "true" means closed and "false" means open
    LoRa.print(CSV_Separator());
  */
  // Write Battery Bank voltage
  LoRa.print(BatteryBankRead());
  LoRa.print(CSV_Separator());
  // Write Motor Current reading (motor current)
  LoRa.print(MotorCurrentRead());
  LoRa.print(CSV_Separator());
  // Write the potentiometer state that controls the motor
  LoRa.print(PotentiometerRead());
  LoRa.print(CSV_Separator());
  // Write Solar Modules voltage
  LoRa.print(PhotovoltaicModulesRead());
  LoRa.print(CSV_Separator());
  // Write Current input on the battery bank  (using the ADS1115)
  LoRa.print(BatteryCurrentRead());
  LoRa.print(CSV_Separator());
  // Write Auxiliary Battery voltage
  LoRa.print(AuxiliaryBatteryRead());
  LoRa.print(CSV_Separator());
  // Write Auxiliary Battery current (using acs712)
  LoRa.print(AuxiliaryBatteryCurrentRead());
  LoRa.print(CSV_Separator());
  /*
    //Write left cooler tension
    LoRa.print(CoolerLeftRead());
    LoRa.print(CSV_Separator());
    //Write right cooler tension
    LoRa.print(CoolerRightRead());
    LoRa.print(CSV_Separator());
  */
  // Write left pump state
  LoRa.print(LeftPumpRead());
  LoRa.print(CSV_Separator());
  // Write right pump state
  LoRa.print(RightPumpRead());
  LoRa.print(CSV_Separator());
  // Write Battery CurrentIn (using the ADS1115)
  //LoRa.print("Bat.BC: ");
  //LoRa.print(BatteryCurrentRead());

  LoRa.endPacket();

  delay(10);
}

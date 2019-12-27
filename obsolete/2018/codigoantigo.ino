#include <ESP8266WiFi.h>

#include "DHT.h"

#define MAXTAM 100
 
#define DHTPIN D2// pino que estamos conectado
#define DHTTYPE DHT22 // DHT 22
 
// Conecte pino 1 do sensor (esquerda) ao +5V
// Conecte pino 2 do sensor ao pino de dados definido em seu Arduino
// Conecte pino 4 do sensor ao GND
// Conecte o resistor de 10K entre pin 2 (dados) 
// e ao pino 1 (VCC) do sensor

DHT dht(DHTPIN, DHTTYPE);



//------------------------------------------------------
//Pinos ESP
#define S0 D4
#define S1 D5
#define S2 D6
#define S3 D7
#define ANALOG_INPUT A0
//------------------------------------------------------

//------------------------------------------------------
//Relações divisores de tensão
float aRef=1;
float relacaoC0= 61.287;//Baterias
float relacaoC1= 87.912;//Placas
//float relacaoS1=//Shunt 1
//------------------------------------------------------

//------------------------------------------------------
// Wi-Fi Settings
const char* ssid = "Solares"; // your wireless network name (SSID)
const char* password = "Solares@1234567"; // your Wi-Fi network password
WiFiClient client;

//------------------------------------------------------

const int postingInterval = 7 * 1000; // post data every 16(2+2) seconds

//------------------------------------------------------
// Canal 1 - Baterias
// ThingSpeak Settings

const int channelID1 = 570781;
String writeAPIKey1 = "3NC6KQ6NP4549VWA"; // write API key for your ThingSpeak Channel
const char* server = "api.thingspeak.com";

//------------------------------------------------------

//------------------------------------------------------
// Canal 2 - Placas
// ThingSpeak Settings
const int channelID2 = 570793;
String writeAPIKey2 = "MNX4MP19O5IB6UVF"; // write API key for your ThingSpeak Channel
//const char* server = "api.thingspeak.com";

//------------------------------------------------------

//------------------------------------------------------
// Canal 3 - Shunt1
// ThingSpeak Settings
const int channelID3 = 570794;
String writeAPIKey3 = "4DW42XQJY4X27JBB"; // write API key for your ThingSpeak Channel
//const char* server = "api.thingspeak.com";

//------------------------------------------------------


//------------------------------------------------------
// Canal 4 - Shunt2
// ThingSpeak Settings
const int channelID4 = 572100;
String writeAPIKey4 = "IG6A9OXFDOZM5N9Y"; // write API key for your ThingSpeak Channel
//const char* server = "api.thingspeak.com";




//------------------------------------------------------
// Canal 5 - Temeperature
// ThingSpeak Settings
const int channelID5 = 572107;
String writeAPIKey5 = "PBU4MWCF2ZLEHBKN"; // write API key for your ThingSpeak Channel
//const char* server = "api.thingspeak.com";

//------------------------------------------------------


//------------------------------------------------------
// Canal 6 - Humidity
// ThingSpeak Settings
const int channelID6 = 572110;
String writeAPIKey6 = "EDDA22O5JMIF3SN4"; // write API key for your ThingSpeak Channel
//const char* server = "api.thingspeak.com";

//------------------------------------------------------


//------------------------------------------------------
// Canal 7 - Offset
// ThingSpeak Settings
const int channelID7 = 573414;
String writeAPIKey7 = "46CXU2WWNDLDG84K"; // write API key for your ThingSpeak Channel
//const char* server = "api.thingspeak.com";

//------------------------------------------------------

// Canal 8 - Offset 2
// ThingSpeak Settings
const int channelID8 = 573906;
String writeAPIKey8 = "Y6YJXUQ63CNR613S"; // write API key for your ThingSpeak Channel
//const char* server = "api.thingspeak.com";

void setup() {

 
  //Deifne output pins for Mux

  Serial.begin(9600);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);     
  pinMode(S2, OUTPUT);     
  pinMode(S3, OUTPUT);

  Serial.println("DHTxx test!");
  dht.begin();


  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void changeMux(int d, int c, int b, int a) {
  
  digitalWrite(S0, a);
  digitalWrite(S1, b);
  digitalWrite(S2, c);
  digitalWrite(S3, d);

  delay(200);
  
}

void loop() {

  float value=0, voltage=0;
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Offset
//Canal 7
  changeMux(HIGH, HIGH, HIGH, HIGH);//1111 = C15

  int offset = analogRead(ANALOG_INPUT);
  
  Serial.print("Offset = ");
  Serial.println(offset);

if (client.connect(server, 80)) {
    
    // Construct API request body
    String body = "field1=";
           body += String(offset);

    client.println("POST /update HTTP/1.1");
    client.println("Host: api.thingspeak.com");
    client.println("User-Agent: ESP8266 (nothans)/1.0");
    client.println("Connection: close");
    client.println("X-THINGSPEAKAPIKEY: " + writeAPIKey7);
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Content-Length: " + String(body.length()));
    client.println("");
    client.print(body);

  }
  client.stop();

delay(1500);//para mux e client

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------  
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------  
//Baterias
//Canal 1
if (client.connect(server, 80)) {

  //------------------------------------------------------------------------------
  //Leitura Baterias
  changeMux(LOW, LOW, LOW, LOW);//0000 = C0
  value = analogRead(ANALOG_INPUT); //Value of the sensor connected Option 0 pin of Mux
  voltage = ((3.1)*(relacaoC0*value)/1023.0);//não sei porque mas tem que multiplicar por 3.1
  Serial.printf("C0 = %.4f\n", voltage);

  //-------------------------------------------------------------------------------

    
    // Construct API request body
    String body = "field1=";
           body += String(voltage);

    client.println("POST /update HTTP/1.1");
    client.println("Host: api.thingspeak.com");
    client.println("User-Agent: ESP8266 (nothans)/1.0");
    client.println("Connection: close");
    client.println("X-THINGSPEAKAPIKEY: " + writeAPIKey1);
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Content-Length: " + String(body.length()));
    client.println("");
    client.print(body);

  }
  client.stop();

delay(1500);//para mux e client
  
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Placas
//Canal 2
if (client.connect(server, 80)) {


  //-------------------------------------------------------------------------------
  //Placas
  changeMux(LOW, LOW, LOW, HIGH);//0001 = C1
  value = analogRead(ANALOG_INPUT); //Value of the sensor connected Option 1 pin of Mux
  voltage = ((3.1)*(relacaoC1*value)/1023.0);//Não sei porque mas tem que multiplicar por 3.1
  Serial.printf("C1 = %.4f\n", voltage);

  //-------------------------------------------------------------------------------


    
    // Construct API request body
    String body = "field1=";
           body += String(voltage);

    client.println("POST /update HTTP/1.1");
    client.println("Host: api.thingspeak.com");
    client.println("User-Agent: ESP8266 (nothans)/1.0");
    client.println("Connection: close");
    client.println("X-THINGSPEAKAPIKEY: " + writeAPIKey2);
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Content-Length: " + String(body.length()));
    client.println("");
    client.print(body);

  }
  client.stop();

delay(1500);//para mux e client

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------





//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

//Shunt1
  changeMux(LOW, LOW, HIGH, LOW);//0010 = C2
  

  int vetorMedidas[MAXTAM];
  int vetorMedias[MAXTAM];
  int mediaDasMedias=0;      //media das medias
  int i=0, j=0;
  float mediaSimples=0;    // media simples
  float tensaoMediaDasMedias;  // media da media das tensoes
  //testar offset variavel
  
  
  for ( i=0 ; i < MAXTAM ; i++ ) {    // laco que calcula a media das medias
    for ( j=0 ; j < MAXTAM ; j++ ) {  // laco que calcula a media simples
      vetorMedidas[j] = analogRead(ANALOG_INPUT);
      mediaSimples += vetorMedidas[i];
    }
    mediaSimples /= MAXTAM;
    vetorMedias[i] = mediaSimples;
    mediaSimples =0;
    mediaDasMedias += vetorMedias[i];
    
  }
  
  mediaDasMedias/= MAXTAM;
  mediaDasMedias -= offset;  // retirada do nivel logico quando o A0 eh aterrado
  tensaoMediaDasMedias= ( (  mediaDasMedias * (3.1/1023) ) * 1000 ) ; // conversao para a tensao

  float corrente;
  corrente = (200 / 75.0) * tensaoMediaDasMedias;
  
  Serial.print("Logico medio medio  (em int): ");//valor entre 0 e 1023
  Serial.println(mediaDasMedias);
  Serial.print("Tensao media media  (em mV) : ");//valor real
  Serial.println(tensaoMediaDasMedias, 6);
  Serial.print("Corrente usando media (em A): "); //valor real
  Serial.println(corrente, 6);



if (client.connect(server, 80)) {

    // Construct API request body
    String body = "field1=";
           body += String(corrente);

    client.println("POST /update HTTP/1.1");
    client.println("Host: api.thingspeak.com");
    client.println("User-Agent: ESP8266 (nothans)/1.0");
    client.println("Connection: close");
    client.println("X-THINGSPEAKAPIKEY: " + writeAPIKey3);
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Content-Length: " + String(body.length()));
    client.println("");
    client.print(body);

  }

    client.stop();

delay(1500);//para mux e client


//--------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------

  changeMux(HIGH, HIGH, HIGH, HIGH);//1111 = C15

  int offset2 = analogRead(ANALOG_INPUT);
  
  Serial.print("Offset = ");
  Serial.println(offset2);

if (client.connect(server, 80)) {
    
    // Construct API request body
    String body = "field1=";
           body += String(offset2);

    client.println("POST /update HTTP/1.1");
    client.println("Host: api.thingspeak.com");
    client.println("User-Agent: ESP8266 (nothans)/1.0");
    client.println("Connection: close");
    client.println("X-THINGSPEAKAPIKEY: " + writeAPIKey8);
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Content-Length: " + String(body.length()));
    client.println("");
    client.print(body);

  }
  client.stop();

delay(1500);//para mux e client

//-------------------------------------------------------------------------------
  //Shunt2
  changeMux(LOW, LOW, HIGH, HIGH);//0011 = C3


  mediaDasMedias=0;      //media das medias
  i=0;
  j=0;
  mediaSimples=0;    // media simples
  tensaoMediaDasMedias=0;  // media da media das tensoes
  //testar offset variavel
  
  
  for ( i=0 ; i < MAXTAM ; i++ ) {    // laco que calcula a media das medias
    for ( j=0 ; j < MAXTAM ; j++ ) {  // laco que calcula a media simples
      vetorMedidas[j] = analogRead(ANALOG_INPUT);
      mediaSimples += vetorMedidas[i];
    }
    mediaSimples /= MAXTAM;
    vetorMedias[i] = mediaSimples;
    mediaSimples =0;
    mediaDasMedias += vetorMedias[i];
    
  }
  
  mediaDasMedias/= MAXTAM;

  
  mediaDasMedias -= offset2;  // retirada do nivel logico quando o A0 eh aterrado
  tensaoMediaDasMedias= ( (  mediaDasMedias * (3.1/1023) ) * 1000 ) ; // conversao para a tensao

  corrente = (200 / 75.0) * tensaoMediaDasMedias;
  
  Serial.print("Logico medio medio  (em int): ");//valor entre 0 e 1023
  Serial.println(mediaDasMedias);
  Serial.print("Tensao media media  (em mV) : ");//valor real
  Serial.println(tensaoMediaDasMedias, 6);
  Serial.print("Corrente usando media (em A): "); //valor real
  Serial.println(corrente, 6);


if (client.connect(server, 80)) {
  
    // Construct API request body
    String body = "field1=";
           body += String(corrente);

    client.println("POST /update HTTP/1.1");
    client.println("Host: api.thingspeak.com");
    client.println("User-Agent: ESP8266 (nothans)/1.0");
    client.println("Connection: close");
    client.println("X-THINGSPEAKAPIKEY: " + writeAPIKey4);
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Content-Length: " + String(body.length()));
    client.println("");
    client.print(body);

  }

    client.stop();

delay(1500);//para mux e client


//--------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------
//Temeperatura/Umidade 

  // A leitura da temperatura e umidade pode levar 250ms!
  // O atraso do sensor pode chegar a 2 segundos.
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  // testa se retorno é valido, caso contrário algo está errado.
  if (isnan(t) || isnan(h)) 
  {
    Serial.println("Failed to read from DHT");//Controle Serial
  } 
  else
  {//Controle Serial
    Serial.print("Umidade: ");
    Serial.print(h);
    Serial.print(" %t");
    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.println(" *C");
  }


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Conexão Canal 5 - Temperatura

if (client.connect(server, 80)) {

   
    // Construct API request body
    String body = "field1=";
           body += String(t);

    client.println("POST /update HTTP/1.1");
    client.println("Host: api.thingspeak.com");
    client.println("User-Agent: ESP8266 (nothans)/1.0");
    client.println("Connection: close");
    client.println("X-THINGSPEAKAPIKEY: " + writeAPIKey5);
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Content-Length: " + String(body.length()));
    client.println("");
    client.print(body);

  }

    client.stop();

delay(1500);//para mux e client



//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Conexão - Canal 6 - Umidade
if (client.connect(server, 80)) {

   
    // Construct API request body
    String body = "field1=";
           body += String(h);

    client.println("POST /update HTTP/1.1");
    client.println("Host: api.thingspeak.com");
    client.println("User-Agent: ESP8266 (nothans)/1.0");
    client.println("Connection: close");
    client.println("X-THINGSPEAKAPIKEY: " + writeAPIKey6);//Única linha a modificar---------------------------------
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Content-Length: " + String(body.length()));
    client.println("");
    client.print(body);

  }

    client.stop();

delay(1500);//para mux e client


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------  
  

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------  

  
  
  // wait and then post again
  delay(postingInterval);
}

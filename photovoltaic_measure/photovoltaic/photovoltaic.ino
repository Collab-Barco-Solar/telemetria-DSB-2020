// Definições

//Tensao de Circuito Voc - 48.4 V 


// valor dos resistores utilizados no divisor de tensão
#define R1 41000.0
#define R2 3600.0

// tensão maxima de leitura do microcontrolador 
#define Vin 3.3 

// valor do ruido apresentado na medição da porta A0 
// verificar na primeira medida: ajustar a tensão inicial medida para o valor Vin
// #define RUIDO 7.8 

// expressao do divisor de tensao
float FATORRESISTORES = (1/(R2/(R1+R2))); 

// define a quantidade de amostras retiradas para fazer cada medida
#define AMOSTRAS 10 

// função para medir a media de uma porta com valor analógico
float lePorta(uint8_t portaAnalogica) 
{
  float total=0;  
  for (int i=1; i<=AMOSTRAS; i++) 
  {
    total += 1.0 * analogRead(portaAnalogica);
    delay(5);
  }
  return total / (float)AMOSTRAS;
}

void setup() {
    Serial.begin(9600);
    
    Serial.println();
    if(Vin<3.3*((R1+R2)/R2)) Serial.println("Tensão está... ok!");
    else Serial.println("Tensão está... error!");
    
    //if(0.012>(Vout/(R1+R2))) Serial.println("Corrente está... ok!");
    //else Serial.println("Corrente está... error!");
}

void loop() {
  float tensaoA0 = ((lePorta(A0))* FATORRESISTORES);
  Serial.println(tensaoA0,8);
  delay(30000); // 60000 para medidas minuto a minuto
}

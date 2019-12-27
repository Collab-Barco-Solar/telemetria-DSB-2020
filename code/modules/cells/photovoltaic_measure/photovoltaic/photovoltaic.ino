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

// função para medir a media de uma porta com valor analógico
float lePorta(uint8_t portaAnalogica, float fatorDeConversao, int amostras, int delayAmostral) 
{
  float total=0;  
  for (int i=1; i<=amostras; i++) 
  {
    total += 1.0 * analogRead(portaAnalogica);
    delay(delayAmostral);
  }
  return fatorDeCoversao*(total / (float) amostras);
}

void setup() {
    Serial.begin(2000000);
    Serial.println("Start");
}

void loop() {
  float tensaoA0 = ((lePorta(A0, R2/(R1+R2), ))* FATORRESISTORES);
  Serial.println(tensaoA0);
  delay(500); // 60000 para medidas minuto a minuto
}

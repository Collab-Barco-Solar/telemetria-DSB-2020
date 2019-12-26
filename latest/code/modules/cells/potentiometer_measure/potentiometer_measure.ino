
#define ANALOG_PIN 13           // GPIO36 -- Analog input
#define BAUD 2000000            // BAUD serial rate
#define GPIO_ADC_RATIO 3.3/4096 // Conversion rate for the ADC
#define VOLTAGE_DIVIDER_RATIO 5/3.3 // Conversion rate for the ADC
 

double measure, voltage;
double pot_grade;

void setup() {
  pinMode(ANALOG_PIN, INPUT);
  
  Serial.begin(BAUD);
  while (!Serial);
  Serial.println();
  Serial.println("Potentiometer grading test");
  
  
  Serial.println("init ok");
 
  delay(1500);
}
  
  

void loop() {
  
	measure = analogRead(ANALOG_PIN);

  
	voltage = measure * GPIO_ADC_RATIO;
	
	pot_grade = voltage * 2.0 * VOLTAGE_DIVIDER_RATIO;
	
	Serial.print("Voltage: ");
  Serial.print(voltage, 8);
  Serial.print(" Measure: ");
  Serial.print(measure);
  Serial.print(" Grade: ");
  Serial.println(pot_grade, 1);

  delay(50);
  
}

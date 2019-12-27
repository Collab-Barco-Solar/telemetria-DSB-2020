
// Watch out the Baud rate, if too high it may crash or not send

#define BAUD 1000000
#define SD_BAUD 1000000

void setup() {

  Serial.begin(BAUD);
  Serial2.begin(SD_BAUD);
  
}

void loop() {

  int n;
  if (Serial2.available() > 0 ) {
    n = Serial2.read();
    Serial.println(n);
  }
  
  
}

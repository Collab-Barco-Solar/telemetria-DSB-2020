
// Watch out the Baud rate, if too high it may crash or not send
#define BAUD 1000000
#define SD_BAUD 1000000

void setup() {
  
  Serial.begin(BAUD);
  Serial2.begin(SD_BAUD);

}

int n = 0;

void loop() {
  
  Serial2.write(n);
  Serial.println(n);

  n++;

  delay(100);
}

void setup() {
  pinMode(PA5, OUTPUT);
}

void loop() {
  for (int i = 0; i < 255; i++) {
    digitalWrite(PA5, HIGH);
    delayMicroseconds(2000 * i / 255);
   
    digitalWrite(PA5, LOW);
    delayMicroseconds(2000 * (255 - i) / 255);
  }
 
  for (int i = 255; i >= 0; i--) {
    digitalWrite(PA5, HIGH);
    delayMicroseconds(2000 * i / 255);
   
    digitalWrite(PA5, LOW);
    delayMicroseconds(2000 * (255 - i) / 255);
  }
}

//photoresistor.ino - pisca mais rapidamente no escuro, mais lentamente quando ouver luz

int photoPin = A0;
int ledPin = 13;
int x = 0; //o...1023

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
 x = analogRead(photoPin);
 digitalWrite(ledPin, HIGH);
 delay(x/10);
 digitalWrite(ledPin, LOW);
 delay(x/10);
}

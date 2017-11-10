//pot.ino - controla velocidade com queo LED pisca por meio de potenciometro

int potPin = A0;
int ledPin = 13;
int x = 0; //o...1023

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  
 x = analogRead(potPin);
 digitalWrite(ledPin, HIGH);
 delay(x/10);
 digitalWrite(ledPin, LOW);
 delay(x/10);
}

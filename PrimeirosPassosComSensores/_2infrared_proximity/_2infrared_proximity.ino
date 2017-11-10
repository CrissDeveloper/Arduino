//infrared_proximity.ino - acende o LED quando o objeto estiver
//próximo usando o sensor de infra vermelho Dagu

int irPin = 8;
int ledPin = 13;
int objectDetected = LOW;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(irPin, INPUT);
  digitalWrite(irPin, HIGH); //pull-up interno
}

void loop() {
  objectDetected = digitalRead(irPin);
  if (LOW == objectDetected) {
    digitalWrite(ledPin, HIGH);
  }else {
    digitalWrite(ledPin, LOW);
  }
}

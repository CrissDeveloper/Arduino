
const int ledPin = 13;
const int botao = 7;

int val = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(botao, INPUT);
}

void loop() {
  val = digitalRead(botao);
  
  if (val == HIGH) {
    digitalWrite(ledPin, HIGH);
  }else{
    digitalWrite(ledPin, LOW);
  }
}

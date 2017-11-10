//button.ino - acende um LED quando um botão é precionado
//(c) BotBook.com - Karvien, Karvien, Valtokari

int buttonPin = 2;
int ledPin = 13;
int buttonStatus = LOW;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH); //pull-up interno
}

void loop() {
  buttonStatus = digitalRead(buttonPin);
  if (LOW == buttonStatus) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin,LOW);
  }
}

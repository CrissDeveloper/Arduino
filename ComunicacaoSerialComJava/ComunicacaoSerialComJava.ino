#define LedPin 13           //int LedPin = 13;
int dado;                   //variavel que receberá os dados da porta serial

void setup() {
  Serial.begin(9600);       //frequência da porta serial
  pinMode(LedPin, OUTPUT);  //defineo pino LedPin como saída
}

void loop() {
  if (Serial.available() > 0) { //verifica se existe comunicação com a porta serial
    dado = Serial.read();       //lê os dados da porta serial
    switch(dado) {
      case 1:
        digitalWrite(LedPin, HIGH); //liga o pino LedPin
      break;

      case 2:
        digitalWrite(LedPin, LOW);  //desliga o pino LedPin
      break;
    }
  }
}

//LED conectado ao pino 10
int ledPin = 13;

//executa uma vez, quando o sketch inicia
void setup() {
  //define o fino como saida
  pinMode(ledPin, OUTPUT);
}

//executa repetidas vezes
void loop() {

  //3 pontos
  for (int x = 0; x < 3; x++) {
    digitalWrite(ledPin, HIGH);   //acende o LED
    delay(150);                   //espera 150 ms
    digitalWrite(ledPin, LOW);    //apaga o LED
    delay(100);                   //espera 100 ms
  }

  //espera 100 ms para marcar o intervalo entre as letras
  delay(100);

  //3 traços
  for (int x = 0; x < 3; x++) {
    digitalWrite(ledPin, HIGH);   //acende o LED
    delay(400);                   //espera 400 ms
    digitalWrite(ledPin, LOW);    //apaga o LED
    delay(100);                   //espera 100 ms
  }

  //espera 100 ms para marcar o intervalo entre as letras
  delay(100);

  //3 pontos novamente
  for (int x = 0; x < 3; x++) {
    digitalWrite(ledPin, HIGH);   //acende o LED
    delay(150);                   //espera 150 ms
    digitalWrite(ledPin, LOW);    //apaga o LED
    delay(100);                   //espera 100 ms
  }

  //espera 5 segundos antes de repetir o sinal de SOS
  delay(5000);
}

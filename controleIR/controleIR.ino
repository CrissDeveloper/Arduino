//Programa: Teste Controle Remoto IR

#include <IRremote.h> //inclui biblioteca do controle remoto IR

int RECV_PIN = 11;
float armazenaValor;
int pinoLedVermelho = 5;
int pinoLedVerde = 7;

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  pinMode(pinoLedVermelho, OUTPUT);
  pinMode(pinoLedVerde, OUTPUT);
  Serial.begin(9600);
  irrecv.enableIRIn(); //Inicializa o receptor IR
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.print("Valor lido ");
    Serial.println(results.value, HEX);
    armazenaValor = (results.value);
    if (armazenaValor == 0xFF30CF) { //Verifica se a tecla 1 foi acionada  
      digitalWrite(pinoLedVermelho, HIGH); //Acende o led vermelho
    }
    if (armazenaValor == 0xFF18E7) { //Verifica se a tecla 2 foi acionada
      digitalWrite(pinoLedVermelho, LOW); //Apaga o led vemelho
    }
    if (armazenaValor == 0xFF10EF) { //Verifica se a tecla 4 foi acionada
      digitalWrite(pinoLedVerde, HIGH); //Acende o led verde
    }
    if (armazenaValor == 0xFF38C7) { //Verifica se a tecla 5 foi acionada
      digitalWrite(pinoLedVerde, LOW); //Apaga o led verde
    }
    if (armazenaValor == 0xFF52AD) { //Verifica se a tecla 9 foi acionada
      digitalWrite(pinoLedVermelho, LOW); //Apaga todos os leds
      digitalWrite(pinoLedVerde, LOW);
    }
    irrecv.resume(); //Le o próximo valor
  }
}

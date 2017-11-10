/*
 Atividade 06  
 */

int pinoLEDvermelho          = 5;
int pinoLEDamarelo           = 6;
int pinoLEDverde             = 9;
int pinoLEDvermelho_pedestre = 11;
int pinoLEDverde_pedestre    = 12;
int pinoBotao                = 2;

int estadoBotao = 0;

void setup() {
  // pinos de saida
  pinMode(pinoLEDvermelho, OUTPUT);
  pinMode(pinoLEDamarelo,  OUTPUT);
  pinMode(pinoLEDverde,    OUTPUT);
  pinMode(pinoLEDvermelho_pedestre, OUTPUT);
  pinMode(pinoLEDverde_pedestre,    OUTPUT);
  // pino de entrada
  pinMode(pinoBotao, INPUT);
}

void loop(){
  digitalWrite(pinoLEDvermelho_pedestre, HIGH);  
  digitalWrite(pinoLEDverde, HIGH);

  // le o estado do botao
  estadoBotao = digitalRead(pinoBotao);

  // verifica se botao foi pressionado
  if (estadoBotao == HIGH) {
    // semaforo veiculos
    // aguarda 1 minuto (60000 segundos)
    delay(60000);
    // apaga LED verde
    digitalWrite(pinoLEDverde, LOW);
    // acende LED amarelo
    digitalWrite(pinoLEDamarelo, HIGH);
    // aguarda 15 segundos
    delay(15000);
    // apaga LED amarelo
    digitalWrite(pinoLEDamarelo, LOW);
    // acende LED vermelho
    digitalWrite(pinoLEDvermelho, HIGH);
    // semaforo pedestres
    // apaga LED vermelho
    digitalWrite(pinoLEDvermelho_pedestre, LOW);
    // acende LED verde
    digitalWrite(pinoLEDverde_pedestre, HIGH);
    // aguarda 30 segundos
    delay(30000);
    // apaga LED verde
    digitalWrite(pinoLEDverde_pedestre, LOW);
    // pisca LED vermelho 3 vezes
    for( int contador = 0; contador <= 3; contador++ ) {
      digitalWrite(pinoLEDvermelho_pedestre, HIGH);
      delay(500);
      digitalWrite(pinoLEDvermelho_pedestre, LOW);
      delay(500);
    }
    // apaga LED vermelho
    digitalWrite(pinoLEDvermelho, LOW);
  } 
}


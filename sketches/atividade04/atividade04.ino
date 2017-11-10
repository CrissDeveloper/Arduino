/*
 Atividade 04
 */

int pinoBotao = 2;
int pinoLED   = 5;

// variavel para ler o estado do botao (chave tactil)
int estadoBotao = 0;

void setup() {
  // configura o pino como saida
  pinMode(pinoLED, OUTPUT);      
  // configura o pino como entrada
  pinMode(pinoBotao, INPUT);     
}

void loop(){
  // le o estado do botao
  estadoBotao = digitalRead(pinoBotao);

  // verifica se botao foi pressionado
  if (estadoBotao == HIGH) {     
    // se sim, acende o LED    
    digitalWrite(pinoLED, HIGH);  
  } 
  else {
    // caso contrario, apaga o LED
    digitalWrite(pinoLED, LOW); 
  }
}



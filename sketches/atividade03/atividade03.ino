/*
 Atividade 03 - Controle de Luminosidade de LEDs 
 */

int pinoLEDvermelho = 5;
int pinoLEDamarelo  = 6;
int pinoLEDverde    = 9;

int brilho;

void setup()  { 
  pinMode(pinoLEDvermelho, OUTPUT);
  pinMode(pinoLEDamarelo, OUTPUT);
  pinMode(pinoLEDverde, OUTPUT);  
} 

void loop()  { 
  // aumenta o brilho dos LEDs, incrementando de 5 em 5 passos
  for( brilho = 0 ; brilho <= 255; brilho = brilho + 5) { 
    analogWrite(pinoLEDvermelho, brilho);
    analogWrite(pinoLEDamarelo, brilho);
    analogWrite(pinoLEDverde, brilho);    
    // aguarda 30 milisegundos    
    delay(30);                            
  } 
  // diminui o brilho dos LEDs, decrementando de 5 em 5 passos
  for( brilho = 255 ; brilho >= 0; brilho = brilho - 5) { 
    analogWrite(pinoLEDvermelho, brilho);
    analogWrite(pinoLEDamarelo, brilho);
    analogWrite(pinoLEDverde, brilho);    
    // aguarda 30 milisegundos    
    delay(30);                            
  } 
} 



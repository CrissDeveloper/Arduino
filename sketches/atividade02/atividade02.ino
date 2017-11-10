/* 
 Atividade 02 - Pisca LED
 */
int pinoLED = 9;

void setup() {                
  // configura o pino como saida
  pinMode(pinoLED, OUTPUT);       
}

void loop() {
  // envia nível alto para o pino
  digitalWrite(pinoLED, HIGH);

  // aguarda 1 segundo
  delay(1000);

  // envia nível baixo para o pino    
  digitalWrite(pinoLED, LOW); 

  // aguarda 1 segundo    
  delay(1000);    
}

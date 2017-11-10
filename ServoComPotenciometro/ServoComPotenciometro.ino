#include <Servo.h> 
Servo myservo;  // create servo object to control a servo 

// Pino analgico do potenciometro
int potpin = 0;

// Variavel que armazena o valor lido do potenciometro
int val;     

void setup() 
{ 
  // Define que o servo esta ligado a porta 9
  myservo.attach(9);  
} 

void loop() 
{ 
  // Le o valor do potenciometro (valores entre 0 e 1023) 
  val = analogRead(potpin);            

  // Converte o valor pra ser usado no servo (valores entre 0 e 180) 
  val = map(val, 0, 1023, 0, 179);     

  // Move o eixo do servo, de acordo com o angulo
  myservo.write(val); 
}

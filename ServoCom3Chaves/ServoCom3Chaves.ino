// Programa : Controlando o servo com 3 chaves
// Autor: Arduino e Cia

#include <Servo.h> 

Servo myservo;

int val; 
int ChaveEsquerda=3; //Pino a ser ligado na chave esquerda
int ChaveCentral=4;  //Pino a ser ligado na chave central
int ChaveDireita=5;  //Pino a ser ligado na chave direita

void setup() 
{ 
  // Pino de dados do servo conectado ao pino 9 do Arduino
  myservo.attach(9);   
  //Define o pino como entrada
  pinMode(ChaveEsquerda, INPUT);      
  //Aciona o resistor pull-up interno
  digitalWrite(ChaveEsquerda, HIGH);  
  pinMode(ChaveCentral, INPUT);
  digitalWrite(ChaveCentral, HIGH);
  pinMode(ChaveDireita, INPUT);
  digitalWrite(ChaveDireita, HIGH);
} 

void loop() 
{ 
 //Le o valor da Chave Esquerda (On/Off)
 val=digitalRead(ChaveEsquerda);  
   //Caso a chave seja pressionada, movimenta o servo
   if(val!=1) 
    {
       myservo.write(60);  //Move o servo para o angulo de 60 graus
       delay(15);          //Delay para o servo atingir a posiçao
    }

 val=digitalRead(ChaveCentral);
   if(val!=1)
    {
       myservo.write(90);  //Move o servo para o angulo de 90 graus
       delay(15);
    }

 val=digitalRead(ChaveDireita);
   if(val!=1)
    {
       myservo.write(120);  //Move o servo para o angulo de 120 graus
       delay(15);
    }
}

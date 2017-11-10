/*
   Teste do Sensor Ultrassônico HC-SR04
   
   Objetivo: medir a distância em centímetros exibindo os dados via serial monitor
   
   Autor: Eng. Wagner Rambo
   
   Data: Fevereiro de 2015
   
   Embedded System: Arduino Duemilanove

*/

#define trig 9  //Pino 9 do Arduino será a saída de trigger
#define echo 8  //Pino 8 do Arduino será a entrada de echo


void trigPuls();  //Função que gera o pulso de trigger

float pulse;     //Variável que armazena o tempo de duração do echo
float dist_cm;   //Variável que armazena o valor da distância em centímetros


void setup() 
{
  pinMode(trig, OUTPUT);   //Pino de trigger será saída digital
  pinMode(echo, INPUT);    //Pino de echo será entrada digital
  
  digitalWrite(trig, LOW); //Saída trigger inicia em nível baixo
  
  Serial.begin(9600);      //Inicia comunicação serial

}

void loop() 
{
   trigPulse();                 //Aciona o trigger do módulo ultrassônico
   
   pulse = pulseIn(echo, HIGH); //Mede o tempo em que o pino de echo fica em nível alto
   
   dist_cm = pulse/58.82;       //Valor da distância em centímetros
   
   // 340m/s
   // 34000cm/s
   
   /*
        100000 us - 17000 cm/s
             x us - 1cm
           1E6
      x = -----
          17E3
   */
   
   Serial.println(dist_cm);     //Imprime o valor na serial
   
   delay(500);                  //Taxa de atualização
   
  

}

void trigPulse()
{
  digitalWrite(trig, HIGH);  //Pulso de trigger em nível alto
  delayMicroseconds(10);     //duração de 10 micro segundos
  digitalWrite(trig, LOW);   //Pulso de trigge em nível baixo
}

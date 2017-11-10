/*
Modos:
1- Normal
2- Amarelo Piscante
3- Manual 

Estados:
1- 1Vd - 2Vm
2- 1Am - 2Vm
3- 1Vm - 2Vd
4- 1Vm - 2Am

Velocidades:
1-Rápido
2-Normal
3-Lento
*/

#include <EEPROM.h>

#define pin1Vm 11
#define pin1Am 12
#define pin1Vd 13

#define pin2Vm 5
#define pin2Am 6
#define pin2Vd 7

#define delayV1 5;
#define delayV1Am 1;
#define delayV2 20;
#define delayV2Am 6;
#define delayV3 80;
#define delayV3Am 12;

byte modo;
byte estado;
byte velocidade;

byte modoAnt;
byte estadoAnt;

byte startMode;
byte startVelo;
byte pisca;
int delayControl;
int cicloSemaforo;

String comando;
char serialBuff;

void setup() {
  
  pinMode(pin1Vm, OUTPUT); //Pino Vermelho  - Semaforo 1
  pinMode(pin1Am, OUTPUT); //Pino Amarelo   - Semaforo 1
  pinMode(pin1Vd, OUTPUT); //Pino Verde     - Semaforo 1

  pinMode(pin2Vm, OUTPUT); //Pino Vermelho - Semaforo 2
  pinMode(pin2Am, OUTPUT); //Pino Amarelo  - Semaforo 2
  pinMode(pin2Vd, OUTPUT); //Pino Verde    - Semaforo 2

  //Lê modo de inicio e grava o próximo modo de inicio na EEPROM
  startMode = EEPROM.read(0);
  if (startMode == 0){
     EEPROM.write(0, 1);
  } else { 
     EEPROM.write(0, 0);
  }

  //Lê modo de inicio e grava o próximo modo de inicio na EEPROM
  startVelo = EEPROM.read(1);
  if ((startVelo < 1) || (startVelo > 3)) { 
     startVelo = 2; //Velocidade Inicial = Normal
     EEPROM.write(1, 2);
  } 

  //Inicia as variaveis
  modo   = startMode + 1;
  estado = 1; 
  velocidade = startVelo; 
  pisca  = 0;
  delayControl = 0;
  cicloSemaforo = 0;

  modoAnt = 99; //Força a primeira execução
  estadoAnt = 99; //Força a primeira execução

  comando = "";
  
  Serial.begin(9600);
}

void loop() {

  if (delayControl < 49) {  //Executa 49 ciclos sem atividade, porém recebendo comandos. As atividades são executadas apenas no ciclo 50.
    
    while (Serial.available() > 0) {
       serialBuff = Serial.read();
       comando = comando + serialBuff;
    }

    if (comando != "") {

       if ((comando.substring(0,1) == "V") || (comando.substring(0,1) == "v")) {  //Velocidade
           if (comando.substring(1,2) == "1") { velocidade = 1; }  //Rápido
           if (comando.substring(1,2) == "2") { velocidade = 2; }  //Normal
           if (comando.substring(1,2) == "3") { velocidade = 3; }  //Lento            
           cicloSemaforo = 0;
           EEPROM.write(1, velocidade);
        }
        
        if ((comando.substring(0,1) == "M") || (comando.substring(0,1) == "m")) {  //Modo
           if (comando.substring(1,2) == "1") { modo = 1; }  //Normal
           if (comando.substring(1,2) == "2") { modo = 2; }  //Amarelo Piscante
           if (comando.substring(1,2) == "3") { modo = 3; }  //Manual  

           cicloSemaforo = 0;
           delayControl = 50;
           estadoAnt = 99; //Força a execução
        }

        if (comando.substring(0,1) == "*") {  //Muda o estado do semáforo
           estado++;
           if (estado > 4) { estado = 1; }        

           delayControl = 50; //Força a execução imediata
        }

        comando = "";
    }

    delayControl++;
  } else {

    if ((modo == 1) || (modo == 3)) { //Modo Automático ou Manual

        if (modo != modoAnt) { //Inicia o estado para quando o modo for alterado para normal (também é executado quando iniciado)
           estado = 1;
           cicloSemaforo = 0;
        } 

        if (cicloSemaforo > 0) { //Conta os ciclos para mudar de fase
           cicloSemaforo--;
        } else { 

           if (modo == modoAnt) { //Inicia o estado para quando o modo for alterado para normal (também é executado quando iniciado)
              if (modo == 1) { //Se for modo Automático
                 estado++;
                 if (estado > 4) { estado = 1; }          
              }   
           }
          
           //Atualiza o tempo do ciclo
           if ((estado == 1) || (estado == 3)) {
               switch (velocidade) {
                  case 1: //Rápido
                       cicloSemaforo = delayV1;   
                       break;
                  case 2: //Normal
                       cicloSemaforo = delayV2; 
                       break;
                  default: //Lento
                       cicloSemaforo = delayV3;
                       break;
               }
            
           } else {
               switch (velocidade) {
                  case 1: //Rápido
                       cicloSemaforo = delayV1Am;   
                       break;
                  case 2: //Normal
                       cicloSemaforo = delayV2Am; 
                       break;
                  default: //Lento
                       cicloSemaforo = delayV3Am;
                       break;
               }   
           }
        }

        //Processa o Estado
        if (estado != estadoAnt) {
            switch (estado) {
               case 1: //1Vd - 2Vm
                    digitalWrite(pin1Vm, LOW);
                    digitalWrite(pin1Am, LOW);
                    digitalWrite(pin2Vd, LOW);
                    digitalWrite(pin2Am, LOW);
                  
                    digitalWrite(pin1Vd, HIGH);                 
                    digitalWrite(pin2Vm, HIGH);                   
                    break;
               case 2: //1Am - 2Vm
                    digitalWrite(pin1Vm, LOW);
                    digitalWrite(pin1Vd, LOW);
                    digitalWrite(pin2Vd, LOW);
                    digitalWrite(pin2Am, LOW);
      
                    digitalWrite(pin1Am, HIGH);                 
                    digitalWrite(pin2Vm, HIGH);                 
                    break;
               case 3: //1Vm - 2Vd
                    digitalWrite(pin1Vd, LOW);
                    digitalWrite(pin1Am, LOW);
                    digitalWrite(pin2Am, LOW);
                    digitalWrite(pin2Vm, LOW);
      
                    digitalWrite(pin1Vm, HIGH);                 
                    digitalWrite(pin2Vd, HIGH);                 
                    break;
               case 4: //1Vm - 2Am
                    digitalWrite(pin1Vd, LOW);
                    digitalWrite(pin1Am, LOW);
                    digitalWrite(pin2Vd, LOW);
                    digitalWrite(pin2Vm, LOW);
      
                    digitalWrite(pin1Vm, HIGH);                 
                    digitalWrite(pin2Am, HIGH);                 
                    break;
            }
  
            estadoAnt = estado;
        }      
    }

    if (modo == 2) { //Modo Piscante
  
       digitalWrite(pin1Vm, LOW);
       digitalWrite(pin1Vd, LOW);
       digitalWrite(pin2Vm, LOW);
       digitalWrite(pin2Vd, LOW);
       
       if (pisca == 0) {
          digitalWrite(pin1Am, LOW);
          digitalWrite(pin2Am, LOW);
          pisca = 1;
       } else {
          digitalWrite(pin1Am, HIGH);
          digitalWrite(pin2Am, HIGH);
          pisca = 0;        
       }
        
    }     

    delayControl = 0;
    modoAnt = modo;    
  }

  delay(10);
}

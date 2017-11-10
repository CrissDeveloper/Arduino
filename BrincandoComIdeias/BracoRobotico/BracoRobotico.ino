#include <VarSpeedServo.h>

#define tempoPausaEntreMovimentos 500  //configura o tempo de pausa entre cada movimento

#define pinServo1  13
#define pinServo2  12
#define pinServo3  11
#define pinServo4  10
#define pinServo5  9
#define pinServo6  8

#define pinBotao1     3
#define pinBotao2     2

#define pinLedA       5
#define pinLedB       4

#define pinPot1      A5
#define pinPot2      A4
#define pinPot3      A3
#define pinPot4      A0
#define pinPot5      A1
#define pinPot6      A2

VarSpeedServo servo1;
VarSpeedServo servo2;
VarSpeedServo servo3;
VarSpeedServo servo4;
VarSpeedServo servo5;
VarSpeedServo servo6;

byte pinBotao1Modo();
bool pinBotao2Retencao();
void pinLedAPisca(bool reset = false);

void setup() {
  servo1.attach(pinServo1);
  servo2.attach(pinServo2);
  servo3.attach(pinServo3);
  servo4.attach(pinServo4);
  servo5.attach(pinServo5);
  servo6.attach(pinServo6);  

  pinMode(pinLedA, OUTPUT);
  pinMode(pinLedB, OUTPUT);

  pinMode(pinBotao1, INPUT_PULLUP);
  pinMode(pinBotao2, INPUT_PULLUP);
}

void loop() {
static byte modo = 1;
static byte modoAnt;
static byte movimento = 0;
static byte memoria[20][5];
static byte posMemoria = 0;
static int ultMemoria = -1;
static unsigned long delayPausa;

  //Modo Normal
  if (modo == 0) {
     digitalWrite(pinLedA, LOW);

     if (pinBotao2Retencao()) {
        digitalWrite(pinLedB, HIGH);

        //executa um movimento  
        if (movimento == 0) {
          byte velocidade = map(analogRead(pinPot6),0,1023,0,255);  
          servo1.slowmove(memoria[posMemoria][0], velocidade);
          servo2.slowmove(memoria[posMemoria][1], velocidade);
          servo3.slowmove(memoria[posMemoria][2], velocidade);
          servo4.slowmove(memoria[posMemoria][3], velocidade);
          servo5.slowmove(memoria[posMemoria][4], velocidade);
          servo6.slowmove( map(memoria[posMemoria][2], 0, 179, 179, 0), velocidade);
          movimento = 1;
        } 

        //aguarda término de um movimento para selecionar o próximo movimento 
        if (movimento == 1) {
          if ( (servo1.read() == memoria[posMemoria][0]) &&
               (servo2.read() == memoria[posMemoria][1]) &&
               (servo3.read() == memoria[posMemoria][2]) &&
               (servo4.read() == memoria[posMemoria][3]) &&
               (servo5.read() == memoria[posMemoria][4]) ) {
  
             posMemoria++;
             if (posMemoria > ultMemoria) { posMemoria = 0; }
             
             delayPausa = millis();
             movimento = 2;
          } 
        }

        //pausa entre movimentos
        if (movimento == 2) {
           if ((millis() - delayPausa) > tempoPausaEntreMovimentos) {
              movimento = 0;
           }
        }
        
     } else {
        digitalWrite(pinLedB, LOW);
        
        if (pinBotao1Modo() == 2) {
           modo = 1;
        }
     }
  }

  //Modo Gravação
  if (modo == 1) {

     if (modoAnt == 0) {
        pinLedAPisca(true);
        ultMemoria = -1;         
     }
    
     digitalWrite(pinLedB, LOW);
     pinLedAPisca();

     if (pinBotao1Modo() == 2) {
        modo = 0;
     }

     servo1.write( map(analogRead(pinPot1),0,1023,0,179) );
     servo2.write( map(analogRead(pinPot2),0,1023,0,179) );
     servo3.write( map(analogRead(pinPot3),0,1023,0,179) );
     servo4.write( map(analogRead(pinPot4),0,1023,0,179) );
     
     servo5.write( map(analogRead(pinPot5),0,1023,0,179) );  //Servos sincronizados inversamente
     servo6.write( map(analogRead(pinPot3),0,1023,179,0) ); 

     if (pinBotao2Apertado()) {
        ultMemoria++;
        memoria[ultMemoria][0] = map(analogRead(pinPot1),0,1023,0,179);
        memoria[ultMemoria][1] = map(analogRead(pinPot2),0,1023,0,179);
        memoria[ultMemoria][2] = map(analogRead(pinPot3),0,1023,0,179);
        memoria[ultMemoria][3] = map(analogRead(pinPot4),0,1023,0,179);
        memoria[ultMemoria][4] = map(analogRead(pinPot5),0,1023,0,179);

        digitalWrite(pinLedB, HIGH);
        delay(250);
        digitalWrite(pinLedB, LOW);
     }
  }

  modoAnt = modo;
}

byte pinBotao1Modo() {
#define tempoDebounce 40 //(tempo para eliminar o efeito Bounce EM MILISEGUNDOS)
#define tempoBotao    1500

   bool estadoBotao;
   static bool estadoBotaoAnt; 
   static byte estadoRet = 0;
   static unsigned long delayBotao = 0;
   static byte enviado = 0;

   if ( (millis() - delayBotao) > tempoDebounce ) {
       estadoBotao = digitalRead(pinBotao1);
       if (estadoRet == 0) {
          if ( !estadoBotao && (estadoBotao != estadoBotaoAnt) ) {
             estadoRet = 1;
             delayBotao = millis();
          }
       }

       if (estadoRet == 1) {
          if ( estadoBotao && (estadoBotao != estadoBotaoAnt) ) {
             estadoRet = 0;
          }
       }
   }

   if (estadoRet == 1) {
      if ((millis() - delayBotao) > tempoBotao) {
         estadoRet = 2;
         delayBotao = millis();
       }
   }

   if (estadoRet == 2) {
      enviado++;
          
      if (enviado >= 2) {
         estadoRet = 0;
         delayBotao = millis();
         enviado = 0;
      }        
   }
       
   estadoBotaoAnt = estadoBotao;

   return estadoRet;
}

bool pinBotao2Retencao() {
#define tempoDebounce 40 //(tempo para eliminar o efeito Bounce EM MILISEGUNDOS)

   bool estadoBotao;
   static bool estadoBotaoAnt; 
   static bool estadoRet = false;
   static unsigned long delayBotao = 0;

   if ( (millis() - delayBotao) > tempoDebounce ) {
       estadoBotao = digitalRead(pinBotao2);
       if ( !estadoBotao && (estadoBotao != estadoBotaoAnt) ) {
          estadoRet = !estadoRet;
          delayBotao = millis();
       }
       estadoBotaoAnt = estadoBotao;
   }

   return estadoRet;
}

bool pinBotao2Apertado() {
#define tempoDebounce 40 //(tempo para eliminar o efeito Bounce EM MILISEGUNDOS)

   bool estadoBotao;
   static bool estadoBotaoAnt; 
   static bool estadoRet;
   static unsigned long delayBotao = 0;

   estadoRet = false;
   if ( (millis() - delayBotao) > tempoDebounce ) {
       estadoBotao = digitalRead(pinBotao2);
       if ( !estadoBotao && (estadoBotao != estadoBotaoAnt) ) {
          estadoRet = true;
          delayBotao = millis();
       }
       estadoBotaoAnt = estadoBotao;
   }

   return estadoRet;
}

void pinLedAPisca(bool reset) {
static unsigned long delayPisca = 0;

   if (reset) {
      delayPisca = millis();
   } else {

     if ((millis() - delayPisca) < 500) {
        digitalWrite(pinLedA, LOW);
     } else {
        digitalWrite(pinLedA, HIGH);
     }
     
     if ((millis() - delayPisca) >= 1000) {
        delayPisca = millis();
     }  
   }
}


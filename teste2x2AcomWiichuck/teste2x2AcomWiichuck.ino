#include <Wire.h>
#include "nunchuck_funcs.h"

int loop_cnt = 0;

byte accx, accy, zbut, cbut, joyx, joyy;

const int motorA = 5; //velocidade motor A - de 0 a 255
const int motorB = 6; //velocidade motor B - de 0 a 255
const int dirA = 7; //direção do motor A - HIGH ou LOW
const int dirB = 8; //direção do motor B - HIGH ou LOW

void setup() {
  Serial.begin(19200);
  //Seta os pinos de alimentacao
  nunchuck_setpowerpins();
  //Inicializa o controle 
  nunchuck_init();

  Serial.println("Teste WiiChuckDemo Arduino");
  
  /*pinMode(motorA, OUTPUT);
  pinMode(motorB, OUTPUT);
  pinMode(dirA, OUTPUT);
  pinMode(dirB, OUTPUT);*/
}

void loop() {

  //Leitura a cada 100ms
  if ( loop_cnt > 100 ) { 
    loop_cnt = 0;

    //Le os dados do Nunchuck
    nunchuck_get_data();
    //Datos do Joystick
    joyx = nunchuck_joyx();
    joyy = nunchuck_joyy();

    //Dados do Acelerometro
    accx  = nunchuck_accelx(); // ranges from approx 70 - 182
    accy  = nunchuck_accely(); // ranges from approx 65 - 173

    //Dados dos botoes
    zbut = nunchuck_zbutton();
    cbut = nunchuck_cbutton();

    //Imprime os valores no Serial Monitor
    
    Serial.print("Ac.X: "); Serial.print((byte)accx, DEC);
    Serial.print("\tAc.Y: "); Serial.print((byte)accy, DEC);
    Serial.print("\tBot.Z: "); Serial.print((byte)zbut, DEC);
    Serial.print("\tBot.C: "); Serial.print((byte)cbut, DEC);
    Serial.print("\tJoy.X: "); Serial.print((byte)joyx, DEC);
    Serial.print("\tJoy.Y: "); Serial.println((byte)joyy, DEC);
    
  }
  loop_cnt++;
  delay(1);

  /*if (cbut == 1) {
    digitalWrite(dirA, HIGH); //SENTIDO DE ROTACAO
    digitalWrite(dirB, HIGH);
    analogWrite(motorA, 100); //VELOCIDADE
    analogWrite(motorB, 100);
  }else{
    digitalWrite(dirA, LOW); //SENTIDO DE ROTACAO
    digitalWrite(dirB, LOW);
    analogWrite(motorA, 100); //VELOCIDADE
    analogWrite(motorB, 100);
  }*/
  
  
}

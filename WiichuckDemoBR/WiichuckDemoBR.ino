#include <Wire.h>
#include "nunchuck_funcs.h"

int loop_cnt = 0;

byte accx, accy, zbut, cbut, joyx, joyy;

void setup(){
  Serial.begin(19200);
  //Seta os pinos de alimentacao
  nunchuck_setpowerpins();
  //Inicializa o controle 
  nunchuck_init();

  Serial.println("Teste WiiChuckDemo Arduino");
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
}


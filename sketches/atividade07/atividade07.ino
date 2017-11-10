/*
Atividade 07
 */

#include <math.h>

int pinoNTC   = 4;

int valorLido = 0;

double termistorNTC(int valorAnalogico) {
  double temperatura;
  temperatura = log(((10240000/valorAnalogico) - 10000));
  temperatura = 1 / (0.001129148 + (0.000234125 * temperatura) + (0.0000000876741 * temperatura * temperatura * temperatura));
  //--- converte Kelvin em Celcius
  temperatura = temperatura - 273.15;
  return temperatura;
}

void setup() {
  pinMode(pinoNTC, INPUT);
  Serial.begin(9600);
  delay(5000);   
}

void loop() {
  valorLido = int(termistorNTC(analogRead(pinoNTC)));
  Serial.println( valorLido );
  delay(1000);  
}



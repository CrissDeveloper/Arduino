/*
 Atividade 05
 */

int pinoLED = 9;
int pinoLDR = 0;

float tensaoLida = 0;
int saidaPWM = 0;

void setup()          
{
  pinMode(pinoLED, OUTPUT);
  pinMode(pinoLDR, INPUT);
}

void loop()               
{
  //--- valor lido sera entre 0 e 1023, cada unidade corresponde a 0.0048828125 volts ou arredondando: 0.0049
  tensaoLida = analogRead( pinoLDR ) * 0.0049;
  //--- dividindo 5 volts por 255 temos 0.0196 volts para cada unidade PWM
  saidaPWM = 255 - (tensaoLida / 0.0196);
  analogWrite( pinoLED, saidaPWM );
}


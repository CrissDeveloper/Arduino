//Comunicaçao serial com C# 2
#define LED 13

int valor_AD = 0;
int valor_leituras = 0;
byte i = 0;

void setup() {
  Serial.begin(9600);  //configura comunicação seria com 9600 bps
  pinMode(LED,OUTPUT); //configura pino do led como saída
}

void loop() {
  if (Serial.available()) { //se byte pronto para leitura
    switch(Serial.read()) { //verifica qual caracter recebido
      case 'A':             //caso 'A'
        digitalWrite(LED,!digitalRead(LED)); //inverte estados do LED
      break;

      case 'T':
        Serial.println(valor_AD);
      break;  
    }
  }

  //MEDIA DE LEITURAS
  valor_leituras += analogRead(A0);
  i++;

  if (i == 16) {
    i = 0;
    valor_AD = valor_leituras>>4;
    valor_leituras = 0;
  }
}

//temperature_lm35.ino - temperatura do LM35 em Celsius para o serial

int lmPin = A0;

void setup() {
  Serial.begin(9600);  
}

float tempC() {
  float raw = analogRead(lmPin); //guarda na variavel raw o valor recebido no pino A0
  float percent = raw/1023.0;    //guarda na variavel percent o valor de raw dividido por 1023.0
  float volts = percent*5.0;     //guarda na variavel volts o valor de percent multiplicado por 5.0
  return 100.0*volts;            //retorna o valor da variavel volts multiplicado por 100.0
}

void loop() {
    Serial.println(tempC());
    delay(200); //ms
}

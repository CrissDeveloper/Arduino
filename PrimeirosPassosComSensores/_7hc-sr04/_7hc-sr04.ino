//hc-sr04.ino - distância usando sensor ultrassônico ping

int trigPin = 8;        //transmite pulso de som
int echoPin = 7;        //escuta eco
float v = 331.5+0.6*20; //cálculo da velocidade do som a 20ºC em m/s

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

float distanceCm(3) {
  //envia pulso de som
  digitalWrite(trigPin, LOW);
  delayMicroseconds(3);           //espera 0,000003 segundo = Trêz milionésimos de um segundo
  digitalWrite(trigPin, HIGH);   //transmte o som
  delayMicroseconds(5);           //espera 0,000005 segundo = Cinco milionésimos de um segundo
  digitalWrite(trigPin, LOW);     //finaliza o pulso de som

  //escuta o eco
  float tUs = pulseIn(echoPin, HIGH); //le quanto tempo levou para o pino de eco ir para LOW em microssegundos
  float t = tUs/1000.0/1000.0/2.0;    //converte microssegundos em segundos
  float d = t*v;                      //calcula a distância a partir do tempo multiplicando pela velocidade = m
  return d*100;                       //retorna distância em cm
}

void loop() {
  int d = distanceCm();
  Serial.println(d, DEC); //imprime no monitor serial o valor convertido em numero decimal
  delay(200); //ms
}

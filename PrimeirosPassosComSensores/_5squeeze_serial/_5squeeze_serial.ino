//squeeze_serial.ino - nível de pressão no FlexiForce para o serial

int squeezePin = A0;
int x = -1; //0..1023

void setup() {
  Serial.begin(9600); //bit/s
}

void loop() {
  x = analogRead(squeezePin);
  Serial.println(x);
  delay(500); //ms
}

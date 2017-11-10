#define LED 13

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(LED, HIGH);
  Serial.print(1);
  delay(1000);

  Serial.print(0);
  digitalWrite(LED, LOW);
  delay(1000);
}

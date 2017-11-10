#define LED 13

int entrada = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    entrada = Serial.read();
    if (entrada == '0') {
      digitalWrite(LED, LOW);
    }
    else if (entrada == '1') {
       digitalWrite(LED, HIGH);
    }
  }
}

#define trigger 12

void setup() 
{
  pinMode(trigger, OUTPUT);
  digitalWrite(trigger, LOW);

}

void loop() 
{
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  delay(100);
  
  

}

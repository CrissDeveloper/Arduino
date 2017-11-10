#define LM35 A0 

const float BASE_CELSIUS = 0.4887585532746823069403714565;  
 
void setup() {   
  Serial.begin(9600); 
} 
 
void loop() {   
  Serial.println(lerTemperatura(), 1);   
  delay(5000); 
} 
 
float lerTemperatura() {   
  return (analogRead(LM35) * BASE_CELSIUS);  
} 

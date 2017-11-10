#include <Fuzzy.h>
#include <FuzzyComposition.h>
#include <FuzzyInput.h>
#include <FuzzyIO.h>
#include <FuzzyOutput.h>
#include <FuzzyRule.h>
#include <FuzzyRuleAntecedent.h>
#include <FuzzyRuleConsequent.h>
#include <FuzzySet.h>

const int numOfReadings = 10;
//Número de leituras a serem tomadas / itens na array
int readings[numOfReadings];

int iluminacao_saida = 0;
int LDR = 5; //Sensor de luminosidade
int initPin = 9;
unsigned long pulseTime = 0;

//Instanciando um objeto da biblioteca
Fuzzy* fuzzy = new Fuzzy();

void setup() {
  Serial.begin(9600);

  //Define o pino de inicialização como saída
  pinMode(initPin, OUTPUT);

  //Crie um loop de matriz para iterar sobre cada item na matriz
  for (int thisReading = 0; thisReading < numOfReadings; thisReading++) {
    readings[thisReading] = 0;
  }

  //Criando o FuzzyInput iluminação
  FuzzyInput* iluminacao = new FuzzyInput(1);

  //Criando os FuzzySet que compoem o FuzzyInput iluminacao
  FuzzySet* escuro = new FuzzySet(0, 40, 40, 65); //iluminacao escuro 15º 35º
  iluminacao->addFuzzySet(escuro); //Adicionando a FuzzySet escuro em iluminacao

  FuzzySet* normal = new FuzzySet(30, 50, 50, 70); //iluminacao normal
  iluminacao->addFuzzySet(normal); //Adicionando a FuzzySet escuro em iluminacao

  FuzzySet* Iluminado = new FuzzySet(60, 80, 80, 100); //iluminacao muito normal
  iluminacao->addFuzzySet(Iluminado); //Adicionando a FuzzySet Iluminado em iluminacao

  fuzzy->addFuzzyInput(iluminacao); //Adiciona o FuzzyInput no objeto Fuzzy

  //Criando o FuzzyOutput Brilho do LED
  FuzzyOutput* brilho = new FuzzyOutput(1);

  //Criando os FuzzySet que compoem o FuzzyOutput Brilho do LED
  FuzzySet* baixo = new FuzzySet(0, 80, 80, 130); //Brilho do LED baixo
  brilho->addFuzzySet(baixo); //Adiciona o FuzzySet baixo em brilho
  
  FuzzySet* medio = new FuzzySet(70, 150, 150, 200); //Brilho do LED normal
  brilho->addFuzzySet(medio); //Adiciona o FuzzySet medio em brilho
  
  FuzzySet* elevado = new FuzzySet(150, 190, 255, 255); //Brilho do LED elevado
  brilho->addFuzzySet(elevado); //Adiciona o FuzzySet elevado em brilho

  fuzzy->addFuzzyOutput (brilho); //Adiciona o FuzzyOutput no objeto Fuzzy

  //----------------- Montando as regras Fuzzy -------------------

  //**FuzzyRule "Se iluminacao = escuro ENTAO Brilho do LED = Elevado"
  FuzzyRuleAntecedent* ifiluminacaoescuro = new FuzzyRuleAntecedent(); // Instanciando um Antecedente para a expressao
  ifiluminacaoescuro->joinSingle(escuro); //Adicinando o FuzzySet correspondente ao objeto Antecedente

  FuzzyRuleConsequent* thenbrilhoelevado = new FuzzyRuleConsequent();// Instanciando um Consenormal para a expressao 
  thenbrilhoelevado->addOutput(elevado); // Adicionando o FuzzySet Correspondente ao objeto Consenormal

  //Instanciando um objeto FuzzyRule
  //Passando o Antecedente e o Consenormal da expressao
  FuzzyRule* fuzzyRule01 = new FuzzyRule(1, ifiluminacaoescuro, thenbrilhoelevado);
  fuzzy->addFuzzyRule(fuzzyRule01); //Adicionando o FuzzyRule ao objeto Fuzy

  //**FuzzyRule "SE iluminacao = normal ENTAO Brtilho do LED = medio"
  FuzzyRuleAntecedent* ifiluminacaonormal = new FuzzyRuleAntecedent(); //Instanciando um Antecedente para a expressao
  ifiluminacaonormal->joinSingle(normal); //Adicinando o FuzzySet correspondente ao objeto Antecedente

  FuzzyRuleConsequent* thenbrilhomedio = new FuzzyRuleConsequent(); //Instanciando um Consenormal para a expressao
  thenbrilhomedio->addOutput(medio); //Adicinando o FuzzySet correspondente ao objeto Consenormal

  //Instanciando um objeto FuzzyRule
  //Passando o Antecedente e o Consenormal da expressao
  FuzzyRule* fuzzyRule02 = new FuzzyRule(2, ifiluminacaonormal, thenbrilhomedio);
  fuzzy->addFuzzyRule(fuzzyRule02); //Adicinando o FuzzyRule ao objeto Fuzzy

  //**FuzzyRule "SE iluminacao = Iluminado ENTAO Brilho do LED = baixo"
  FuzzyRuleAntecedent* ifiluminacaoIluminado = new FuzzyRuleAntecedent(); //Instanciando um Antecedente para a expressao
  ifiluminacaoIluminado->joinSingle(Iluminado); //Adicionando o FuzzySet corrspondente ao objeto Antecedente

  FuzzyRuleConsequent* thenbrilhobaixo = new FuzzyRuleConsequent(); //Instanciando um Consenormal para a expressao
  thenbrilhobaixo->addOutput(baixo); //Adicionando o FuzzySet correspondente ao objeto Consenormal

  //Instanciando um objeto FuzzyRule
  //Passando o Antecedente e o Consenormal da expressao
  FuzzyRule* fuzzyRule03 = new FuzzyRule(3, ifiluminacaoIluminado, thenbrilhobaixo);
  fuzzy->addFuzzyRule(fuzzyRule03); //Adicionando o FuzzyRule ao objeto Fuzzy
}

void loop() {
  //Envia 10 pulso de microssegundo
  digitalWrite(initPin, HIGH);
  delayMicroseconds(10); //Aguarda 10 microssegundos antes de desligar
  //Para de enviar o pulso
  digitalWrite(initPin, LOW);
  
  float iluminacao_medida = (analogRead(LDR))*0.09765;
  fuzzy->setInput(1, iluminacao_medida);

  fuzzy->fuzzify();

  int output = fuzzy->defuzzify(1);
  analogWrite(9, output);

  Serial.print(" Iluminacao: ");
  Serial.print(iluminacao_medida);
  Serial.print(" Brilho do LED: ");
  Serial.println(output*0.39215);
  Serial.print(" % ");

  //Aguarda 100 milésimos de segundo antes de fazer o loop novamente
  delay(100);
}

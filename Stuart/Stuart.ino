#include <robo_hardware2.h>
#include "Estrategia.h"

Estrategia e;
Sensores s;

void setup() {
  Serial.begin(9600);
  robo.configurar(false);
  e.calibracao();
  robo.habilitaTCS34();             
}
void loop() {
  //Serial.println("Miro é o mito");
  e.executar();
  //if (s.ehVerdeEsquerdo()) Serial.println("EH VERDE ESQUERDOOOO");
  //Serial.println(robo.getHSVEsquerdo().v);
  //delay(200);
}

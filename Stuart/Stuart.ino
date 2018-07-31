#include <robo_hardware2.h>
#include "Estrategia.h"

Estrategia e;

void setup() {
  Serial.begin(9600);
  robo.configurar(false);
  e.calibracao();             
}
void loop() {
  //Serial.println("Miro é o mito");
  e.executar();
}

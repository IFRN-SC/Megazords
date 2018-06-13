#include <robo_hardware2.h>
#include "Estrategia.h"

Estrategia e;

void setup() {
  robo.configurar(false);
  e.calibracao();
  Serial.print("Deu Certo!");
}
void loop() {
  e.executar();
}

#include <robo_hardware2.h>
#include "Estrategia.h"

Estrategia e;

void setup() {
  robo.configurar(false);
  //e.calibracao();             // Comentar quando não quiser fazer calibração
  Serial.print("Deu Certo!");
}
void loop() {
  e.executar();
}

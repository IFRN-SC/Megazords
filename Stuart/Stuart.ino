#include <robo_hardware2.h>
#include "Estrategia.h"

Estrategia e;

void setup() {
  robo.configurar(false);
  robo.habilitaTCS34();
}
void loop() {
  e.executar();
}
